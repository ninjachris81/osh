package com.osh.value;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;
import com.osh.SerializableIdentifyable;
import com.osh.SerializationSupport;

@DatabaseTable(tableName = "dm_value_groups")
public class ValueGroup {

	@DatabaseField(id = true)
	String id;

	protected ValueGroup() {
	}

	public ValueGroup(String id) {
		this.id = id;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}
}
