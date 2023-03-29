package com.osh.datamodel.meta;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.j256.ormlite.field.DataType;
import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

import java.sql.Blob;

@DatabaseTable(tableName = "dm_audio_playback_sources")
public class AudioPlaybackSource {

    @DatabaseField(id = true)
    private String id;

    @DatabaseField(canBeNull = false)
    private String name;

    @DatabaseField(canBeNull = false, columnName = "source_url")
    private String sourceUrl;

    @DatabaseField(dataType = DataType.BYTE_ARRAY, columnName = "image_icon")
    private byte[] imageIcon;

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getSourceUrl() {
        return sourceUrl;
    }

    public Bitmap getImage() {
        if (imageIcon.length > 0) {
            return BitmapFactory.decodeByteArray(imageIcon, 0, imageIcon.length);
        } else {
            return null;
        }
    }

}
