package com.osh.service.impl;


import com.j256.ormlite.dao.Dao;
import com.j256.ormlite.dao.DaoManager;
import com.osh.actor.ActorBase;
import com.osh.actor.DBActor;
import com.osh.actor.DBAudioActor;
import com.osh.datamodel.DatamodelBase;
import com.osh.datamodel.DynamicDatamodel;
import com.osh.datamodel.meta.AudioPlaybackSource;
import com.osh.datamodel.meta.KnownArea;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.datamodel.meta.KnownRoomActors;
import com.osh.datamodel.meta.KnownRoomValues;
import com.osh.service.IActorService;
import com.osh.service.ICommunicationService;
import com.osh.service.IDatabaseService;
import com.osh.service.IDatamodelService;
import com.osh.service.IValueService;
import com.osh.utils.IObservableBoolean;
import com.osh.utils.ObservableBoolean;
import com.osh.actor.DBShutterActor;
import com.osh.value.DBValue;
import com.osh.value.ValueBase;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.SQLException;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class DatamodelServiceImpl implements IDatamodelService {

	private static final Logger log = LoggerFactory.getLogger(DatamodelServiceImpl.class);

	private final ObservableBoolean loadedState;

	protected Dao<ValueGroup, String> valueGroupDao;
	protected Dao<DBValue, String> valueDao;

	protected Dao<DBActor, String> actorDao;
	protected Dao<DBAudioActor, String> audioActorDao;

	protected Dao<AudioPlaybackSource, String> audioPlaybackSourceDao;
	protected Dao<DBShutterActor, String> shutterActorDao;

	protected Dao<KnownRoom, String> knownRoomsDao;

	protected Dao<KnownArea, String> knownAreaDao;

	protected Dao<KnownRoomValues, String> knownRoomValuesDao;

	protected Dao<KnownRoomActors, String> knownRoomActorsDao;

	private DatamodelBase datamodel;

	private final IDatabaseService databaseService;
	private final IValueService valueService;
	private final IActorService actorService;

	private final ICommunicationService communicationService;

	private final ExecutorService executorService;

	public DatamodelServiceImpl(ICommunicationService communicationService, IDatabaseService databaseService, IValueService valueService, IActorService actorService) throws SQLException {
		this.communicationService = communicationService;
		this.databaseService = databaseService;
		this.valueService = valueService;
		this.actorService = actorService;

		loadedState = new ObservableBoolean(false);

		executorService = Executors.newFixedThreadPool(1);
		executorService.submit(new Runnable() {
			@Override
			public void run() {
				try {
					loadDatamodel();
				} catch (SQLException e) {
					throw new RuntimeException(e);
				} catch (Exception e1) {
					throw new RuntimeException(e1);
				}
			}
		});

	}

	private void loadDatamodel() throws SQLException {
		valueGroupDao = DaoManager.createDao(databaseService.getConnectionSource(), ValueGroup.class);
		valueDao = DaoManager.createDao(databaseService.getConnectionSource(), DBValue.class);
		actorDao = DaoManager.createDao(databaseService.getConnectionSource(), DBActor.class);
		audioActorDao = DaoManager.createDao(databaseService.getConnectionSource(), DBAudioActor.class);
		audioPlaybackSourceDao = DaoManager.createDao(databaseService.getConnectionSource(), AudioPlaybackSource.class);
		shutterActorDao = DaoManager.createDao(databaseService.getConnectionSource(), DBShutterActor.class);
		knownRoomsDao = DaoManager.createDao(databaseService.getConnectionSource(), KnownRoom.class);
		knownAreaDao = DaoManager.createDao(databaseService.getConnectionSource(), KnownArea.class);
		knownRoomValuesDao = DaoManager.createDao(databaseService.getConnectionSource(), KnownRoomValues.class);
		knownRoomActorsDao = DaoManager.createDao(databaseService.getConnectionSource(), KnownRoomActors.class);

		datamodel = new DynamicDatamodel();

		for (KnownArea knownArea : knownAreaDao.queryForAll()) {
			datamodel.addKnownArea(knownArea.getId(), knownArea.getName());
		}

		for (KnownRoom knownRoom : knownRoomsDao.queryForAll()) {
			KnownArea knownArea = datamodel.getKnownArea(knownRoom.getKnownAreaId());
			datamodel.addKnownRoom(knownArea, knownRoom.getId(), knownRoom.getName());
		}

		for (ValueGroup valueGroup : valueGroupDao.queryForAll()) {
			datamodel.addValueGroup(valueGroup.getId());
		}

		for (DBValue value : valueDao.queryForAll()) {
			ValueGroup valueGroup = datamodel.getValueGroup(value.getValueGroupId());
			ValueBase val = null;

			if (value.getClassType().equals("BooleanValue")) {
				val = datamodel.addBooleanValue(valueGroup, value.getId(), ValueType.of(value.getValueType()), ValueBase.VALUE_TIMEOUT.of(value.getValueTimeout()));
			} else if (value.getClassType().equals("IntegerValue")) {
				val = datamodel.addIntegerValue(valueGroup, value.getId(), ValueType.of(value.getValueType()), ValueBase.VALUE_TIMEOUT.of(value.getValueTimeout()));
			} else if (value.getClassType().equals("LongValue")) {
				val = datamodel.addLongValue(valueGroup, value.getId(), ValueType.of(value.getValueType()), ValueBase.VALUE_TIMEOUT.of(value.getValueTimeout()));
			} else if (value.getClassType().equals("DoubleValue")) {
				val = datamodel.addDoubleValue(valueGroup, value.getId(), ValueType.of(value.getValueType()), ValueBase.VALUE_TIMEOUT.of(value.getValueTimeout()));
			} else if (value.getClassType().equals("StringValue")) {
				val = datamodel.addStringValue(valueGroup, value.getId(), ValueType.of(value.getValueType()), ValueBase.VALUE_TIMEOUT.of(value.getValueTimeout()));
			} else if (value.getClassType().equals("EnumValue")) {
				val = datamodel.addEnumValue(valueGroup, value.getId(), ValueType.of(value.getValueType()), ValueBase.VALUE_TIMEOUT.of(value.getValueTimeout()), value.getEnumCount());
			} else {
				log.error("Unknown class type: " + value.getClassType());
			}
			
			valueService.registerValue(val);
		}

		for (KnownRoomValues knownRoomsValue : knownRoomValuesDao.queryForAll()) {
			KnownRoom knownRoom = datamodel.getKnownRoom(knownRoomsValue.getRoomId());
			ValueBase value = datamodel.getValue(knownRoomsValue.getValueId(), knownRoomsValue.getValueGroupId());
			knownRoom.addValue(value);
		}

		for (DBActor actor : actorDao.queryForAll()) {
			ValueGroup valueGroup = datamodel.getValueGroup(actor.getValueGroupId());
			ActorBase act = null;

			if (actor.getClassType().equals("DigitalActor")) {
				act = datamodel.addDigitalActor(valueGroup, actor.getId(), ValueType.of(actor.getValueType()), ValueBase.VALUE_TIMEOUT.of(actor.getValueTimeout()), actor.isAsync());
			} else if (actor.getClassType().equals("ShutterActor")) {
				List<DBShutterActor> matchList = shutterActorDao.queryForFieldValues(Map.of("id", actor.getId(), "value_group_id", valueGroup.getId()));
				if (matchList.size() == 1) {
					DBShutterActor shutterActor = matchList.get(0);
					act = datamodel.addShutterActor(valueGroup, actor.getId(), ValueType.of(actor.getValueType()), ValueBase.VALUE_TIMEOUT.of(actor.getValueTimeout()), shutterActor.isShutterTiltSupport(), shutterActor.getShutterFullCloseDuration(), shutterActor.getShutterFullTiltDuration());
				} else {
					throw new RuntimeException("Unexpected mapping of actor " + actor.getId());
				}
			} else if (actor.getClassType().equals("ToggleActor")) {
				act = datamodel.addToggleActor(valueGroup, actor.getId());
			} else if (actor.getClassType().equals("ValueActor")) {
				act = datamodel.addValueActor(valueGroup, actor.getId(), ValueType.of(actor.getValueType()), ValueBase.VALUE_TIMEOUT.of(actor.getValueTimeout()));
			} else if (actor.getClassType().equals("AudioPlaybackActor")) {
				List<DBAudioActor> matchList = audioActorDao.queryForFieldValues(Map.of("id", actor.getId(), "value_group_id", valueGroup.getId()));
				if (matchList.size() == 1) {
					DBAudioActor audioActor = matchList.get(0);
					act = datamodel.addAudioPlaybackActor(valueGroup, actor.getId(), ValueType.of(actor.getValueType()), ValueBase.VALUE_TIMEOUT.of(actor.getValueTimeout()), audioActor.getAudioDeviceIds(), audioActor.getAudioActivationRelayId(), audioActor.getAudioVolume(), audioActor.getAudioVolumeId(), audioActor.getAudioUrl(), audioActor.getAudioUrlId());
				} else {
					throw new RuntimeException("Unexpected mapping of actor " + actor.getId());
				}
			} else if (actor.getClassType().equals("DoorActor")) {
				act = datamodel.addDoorActor(valueGroup, actor.getId(), ValueType.of(actor.getValueType()), ValueBase.VALUE_TIMEOUT.of(actor.getValueTimeout()));
			} else {
				log.error("Unknown class type: " + actor.getClassType());
			}

			for (AudioPlaybackSource audioPlaybackSource : audioPlaybackSourceDao.queryForAll()) {
				datamodel.addAudioPlaybackSource(audioPlaybackSource);
			}
			
			actorService.registerActor(act);
		}

		for (KnownRoomActors knownRoomActor : knownRoomActorsDao.queryForAll()) {
			KnownRoom knownRoom = datamodel.getKnownRoom(knownRoomActor.getRoomId());
			ActorBase actor = datamodel.getActor(knownRoomActor.getActorId(), knownRoomActor.getValueGroupId());
			knownRoom.addActor(actor);
		}

		loadedState.changeValue(true);

		communicationService.connectMqtt();
	}

	@Override
	public DatamodelBase getDatamodel() {
		return datamodel;
	}

	@Override
	public void save() {

	}

	@Override
	public IObservableBoolean loadedState() {
		return loadedState;
	}
}
