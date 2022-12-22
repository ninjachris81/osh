package com.osh.datamodel;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class DynamicDatamodel extends DatamodelBase {

	private static final Logger log = LoggerFactory.getLogger(DynamicDatamodel.class);

	public DynamicDatamodel() {
		super("DynamicDatamodel");
	}
	
	void deserialize(String data) {
		/*
		ObjectMapper mapper = new ObjectMapper();
		try {
			mapper.readValue(data, DynamicDatamodel.class);
		} catch (JsonProcessingException e) {
			log.error("Object mapper failed", e);
		}*/

		//JsonParser parser = JsonParserFactory.getJsonParser();
		
		//Map<String, Object> map = parser.parseMap(data);
		
		//deserializeMap(map.get("knownDevices"));
	}

	/*
	private void deserializeMap(Object object) {
		if (object instanceof Collection) {
			Collection coll = (Collection) object;
			for (Object mapObj : coll) {
				if (mapObj instanceof Map) {
					Map map = (Map) mapObj;
					
					if (map.containsKey(SerializableIdentifyable.PROPERTY_CLASSTYPE)) {
						String classType = (String) map.get(SerializableIdentifyable.PROPERTY_CLASSTYPE);
						
						SerializationSupport newInstance = null;
						if (classType.equals(KnownDevice.class.getName())) {
							newInstance = new KnownDevice();
						} else if (classType.equals(ValueGroup.class.getName())) {
							newInstance = new ValueGroup();
							
							
						} else if (classType.equals(BooleanValue.class.getName())) {
							newInstance = new BooleanValue();
						} else if (classType.equals(DoubleValue.class.getName())) {
							newInstance = new DoubleValue();
						} else if (classType.equals(IntegerValue.class.getName())) {
							newInstance = new IntegerValue();
						} else if (classType.equals(LongValue.class.getName())) {
							newInstance = new LongValue();
						} else if (classType.equals(StringValue.class.getName())) {
							newInstance = new StringValue();
							
							
						} else if (classType.equals(DigitalActor.class.getName())) {
							newInstance = new DigitalActor();
						} else if (classType.equals(AudioPlaybackActor.class.getName())) {
							newInstance = new AudioPlaybackActor();
							
							
						} else if (classType.equals(KnownRoom.class.getName())) {
							newInstance = new KnownRoom();
						} else if (classType.equals(ProcessorTask.class.getName())) {
							newInstance = new ProcessorTask();
						}
						
					}
				}
			}
		}
	}*/
	
	public String serialize() {
		/*
		ObjectMapper mapper = new ObjectMapper();
		
		mapper.enable(SerializationFeature.WRITE_ENUMS_USING_INDEX);
		
		try {
			return mapper.writeValueAsString(this);
		} catch (JsonProcessingException e) {
			log.error("Failed serializing datamodel", e);
		}*/
		
		return null;
	}


}
