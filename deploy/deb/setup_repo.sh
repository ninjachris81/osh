#!/usr/bin/env bash

# Exit immediately if a command exits with a non-zero status
set -e

# ==============================================================================
# VALIDATE MANDATORY PARAMETERS
# ==============================================================================
# Prüft, ob das erste Argument ($1) übergeben wurde und nicht leer ist
if [[ -z "${1:-}" ]]; then
  echo "❌ Error: DOMAIN_OR_IP is a mandatory parameter." >&2
  echo "Usage: sudo $0 <domain_or_ip>" >&2
  exit 1
fi

# ==============================================================================
# CONFIGURATION - CHANGE THESE TO MATCH YOUR ENVIRONMENT
# ==============================================================================
DOMAIN_OR_IP="$1"                          # Wird nun zwingend als $1 übergeben
CODENAME="bookworm"                        # e.g., bookworm, trixie, jammy, focal
REPO_BASE_DIR="/var/www/debian-repo"
KEY_REAL_NAME="OSH Open Smart Home"
KEY_EMAIL="cbstar@web.de"
KEY_PASSPHRASE="osh"
# ==============================================================================

# Ensure the script is run as root
if [ "$EUID" -ne 0 ]; then
  echo "❌ Please run this script as root or via sudo."
  exit 1
fi

# Rest des Skripts folgt hier...
echo "🚀 Starting setup for domain/IP: $DOMAIN_OR_IP"

echo "🚀 Starting Debian Self-Signed HTTPS Repository Setup..."

# 1. Install Required Packages
echo "📦 Installing required packages..."
apt-get update -y
apt-get install -y reprepro gnupg nginx curl rng-tools openssl

# Ensure entropy generator is running for faster GPG key generation
systemctl start rng-tools || true

# 2. Generate GPG Key Pair Non-Interactively
echo "Removing any existing GPG keys for $KEY_REAL_NAME..."
sudo gpg --homedir /root/.gnupg --delete-secret-keys "$KEY_REAL_NAME" 2>/dev/null || true
sudo gpg --homedir /root/.gnupg --delete-keys "$KEY_REAL_NAME" 2>/dev/null || true

echo "🔑 Generating GPG Signing Key..."
GPG_BATCH_FILE=$(mktemp)

# Bereinigtes Batch-Format für moderne GnuPG-Versionen
cat <<EOF > "$GPG_BATCH_FILE"
     %no-protection
     Key-Type: RSA
     Key-Length: 4096
     Subkey-Type: RSA
     Subkey-Length: 4096
     Name-Real: $KEY_REAL_NAME
     Name-Email: $KEY_EMAIL
     Expire-Date: 0
     %commit
     %echo done
EOF

# Schlüssel generieren
gpg --batch --generate-key "$GPG_BATCH_FILE"
rm -f "$GPG_BATCH_FILE"

# GPG-ID zuverlässig auslesen
KEY_ID=$(gpg --list-secret-keys --keyid-format LONG "$KEY_EMAIL" | grep 'sec' | awk '{print $2}' | cut -d'/' -f2)

if [ -z "$KEY_ID" ]; then
    echo "❌ Failed to retrieve the generated GPG Key ID."
    exit 1
fi
echo "✅ GPG Key Generated successfully. Key ID: $KEY_ID"

# 3. Create Repository Structure
echo "Cleaning up any existing repository structure..."
rm -rf "$REPO_BASE_DIR"
sudo rm -f /etc/nginx/sites-available/debian-repo
sudo rm -f /etc/nginx/sites-enabled/debian-repo
sudo systemctl restart nginx

echo "📂 Creating directory structures..."
mkdir -p "$REPO_BASE_DIR/conf"

# 4. Create reprepro Configuration
echo "📝 Configuring reprepro..."
cat <<EOF > "$REPO_BASE_DIR/conf/distributions"
Origin: $KEY_REAL_NAME
Label: $KEY_REAL_NAME
Codename: $CODENAME
Architectures: arm64 source
Components: main
Description: APT repository for custom packages
SignWith: $KEY_ID
EOF

# 5. Export Public GPG Key
echo "📤 Exporting public GPG key..."
gpg --armor --export "$KEY_ID" > "$REPO_BASE_DIR/public.gpg.key"

# 6. Generate Self-Signed SSL Certificate
echo "🔒 Generating Self-Signed SSL Certificate..."
SSL_DIR="/etc/nginx/ssl"
mkdir -p "$SSL_DIR"

openssl req -x509 -nodes -days 3650 -newkey rsa:4096 \
  -keyout "$SSL_DIR/repo.key" \
  -out "$SSL_DIR/repo.crt" \
  -subj "/CN=$DOMAIN_OR_IP/O=My Repo/C=US"

# Copy the SSL certificate to the public web root so clients can download/trust it
cp "$SSL_DIR/repo.crt" "$REPO_BASE_DIR/server.crt"
chown -R www-data:www-data "$REPO_BASE_DIR"

# 7. Configure Nginx Virtual Host for HTTPS
echo "🌐 Configuring Nginx with HTTPS..."
NGINX_CONF="/etc/nginx/sites-available/debian-repo"

cat <<EOF > "$NGINX_CONF"
server {
    listen 80;
    server_name $DOMAIN_OR_IP;
    return 301 https://\$host\$request_uri;
}

server {
    listen 443 ssl;
    server_name $DOMAIN_OR_IP;

    ssl_certificate $SSL_DIR/repo.crt;
    ssl_certificate_key $SSL_DIR/repo.key;

    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers HIGH:!aNULL:!MD5;

    root $REPO_BASE_DIR;
    index index.html;

    location / {
        autoindex on;
    }

    # Protect internal reprepro management files
    location ~ /(conf|db) {
        deny all;
        return 404;
    }
}
EOF

# Enable Nginx site if not already enabled
if [ ! -f "/etc/nginx/sites-enabled/debian-repo" ]; then
    ln -s "$NGINX_CONF" /etc/nginx/sites-enabled/
fi

# Remove default Nginx site if it conflicts
rm -f /etc/nginx/sites-enabled/default || true

# Test and restart Nginx
nginx -t
systemctl restart nginx

# 8. Generate a Client Onboarding Script (Handles self-signed trust)
echo "📝 Generating client onboarding snippet..."
cat <<EOF > "$REPO_BASE_DIR/client_setup.sh"
#!/usr/bin/env bash
set -e
echo "🔧 Adding Self-Signed HTTPS repository $DOMAIN_OR_IP..."

# 1. Download and trust the self-signed SSL certificate for system tools (curl/wget)
sudo mkdir -p /usr/local/share/ca-certificates
curl -k -fsSL https://$DOMAIN_OR_IP/server.crt -o /tmp/server.crt
sudo cp /tmp/server.crt /usr/local/share/ca-certificates/myrepo.crt
sudo update-ca-certificates

# 2. Download and register the repository GPG key for APT
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://$DOMAIN_OR_IP/public.gpg.key | sudo gpg --dearmor --yes -o /etc/apt/keyrings/myrepo.gpg

# 3. Add the APT source listing
echo "deb [signed-by=/etc/apt/keyrings/myrepo.gpg] https://$DOMAIN_OR_IP/ $CODENAME main" | sudo tee /etc/apt/sources.list.d/myrepo.list

# 4. Refresh package listings
sudo apt-get update
echo "✅ Secure self-signed repository added and trusted successfully!"
EOF

chown www-data:www-data "$REPO_BASE_DIR/client_setup.sh"

echo "=========================================================================="
echo "🎉 SELF-SIGNED HTTPS DEBIAN REPOSITORY SETUP COMPLETE!"
echo "=========================================================================="
echo "🌐 Your repository is hosted securely at: https://$DOMAIN_OR_IP"
echo "🔑 GPG Key ID used: $KEY_ID"
echo ""
echo "🚀 To add a package to this repository, run this command on this server:"
echo "   sudo reprepro -b $REPO_BASE_DIR includedeb $CODENAME /path/to/your-package.deb"
echo ""
echo "💻 Your users can add this repository and trust your SSL certificate by running:"
echo "   curl -k -fsSL https://$DOMAIN_OR_IP/client_setup.sh | bash"
echo "   (Note: The '-k' tells curl to bypass the certificate check just for downloading the setup script itself)"
echo "=========================================================================="
