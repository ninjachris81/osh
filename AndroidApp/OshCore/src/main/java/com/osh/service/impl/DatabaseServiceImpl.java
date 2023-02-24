package com.osh.service.impl;

import com.j256.ormlite.db.DatabaseType;
import com.j256.ormlite.jdbc.JdbcConnectionSource;
import com.j256.ormlite.support.ConnectionSource;
import com.osh.config.IApplicationConfig;
import com.osh.service.IDatabaseService;

import java.sql.Connection;
import java.sql.SQLException;

public class DatabaseServiceImpl implements IDatabaseService {

    private final ConnectionSource connectionSource;

    public DatabaseServiceImpl(IApplicationConfig appConfig) throws SQLException {
        String databaseUrl = "jdbc:postgresql://" + appConfig.getDatabase().getHost() + ":" + appConfig.getDatabase().getPort() + "/" + appConfig.getDatabase().getName();
        // create a connection source to our database
        connectionSource = new JdbcConnectionSource(databaseUrl, appConfig.getDatabase().getUsername(), appConfig.getDatabase().getPassword());
    }

    @Override
    public ConnectionSource getConnectionSource() {
        return connectionSource;
    }
}
