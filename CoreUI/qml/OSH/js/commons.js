var invalidValue = "";

function formatValue(v) {
    return v.rawValue === undefined ? invalidValue : v.rawValue + " " + v.unitTypeSuffix
}

function formatDoubleValue(v, decimalPlaces = 1) {
    return v.rawValue === undefined ? invalidValue : round(v.rawValue, decimalPlaces) + " " + v.unitTypeSuffix
}

function round(num, decimalPlaces = 0) {
    var p = Math.pow(10, decimalPlaces);
    var n = (num * p) * (1 + Number.EPSILON);
    return Math.round(n) / p;
}

function addTypeSuffix(rawValue, unitTypeSuffix, isValid) {
    if (!isValid) return invalidValue;
    return rawValue + " " + ValueManager.unitTypeToSuffix(unitTypeSuffix)
}

function isInv(rawValue) {
    return rawValue === invalidValue;
}

function searchValueIndex(id) {
    return searchIndex(id, DatamodelManager.datamodel.values);
}

function searchActorIndex(id) {
    return searchIndex(id, DatamodelManager.datamodel.actors);
}

function searchIndexByValueType(valueType, coll, globalColl) {
    var localIndex = -1;
    var returnIndex = -1;

    for (var i=0;i<coll.length;i++) {
        if (coll[i].valueType ===valueType) {
            if (localIndex == -1) {
                localIndex = i;
                returnIndex = searchIndex(coll[i].fullId, globalColl)
            } else {
                console.warn("Found more than one value type")
                return -1
            }
        }
    }

    return returnIndex
}

function searchKnownRoomIndex(id) {
    return searchIndex2(id, DatamodelManager.datamodel.knownRooms);
}

function searchIndex(id, coll) {
    for (var i=0;i<coll.length;i++) {
        if (coll[i].fullId ===id) {
            return i;
        }
    }
    console.warn("Unable to find " + id + " in " + coll)
    return -1
}

function searchIndex2(id, coll) {
    for (var i=0;i<coll.length;i++) {
        if (coll[i].id ===id) {
            return i;
        }
    }
    console.warn("Unable to find " + id + " in " + coll)
    return -1
}


function selectValue(id) {
    console.info("Searching value " + id + " in " + DatamodelManager.datamodel.values.length + " values")

    for (var i=0;i<DatamodelManager.datamodel.values.length;i++) {
        if (DatamodelManager.datamodel.values[i].fullId ===id) {
            return DatamodelManager.datamodel.values[i];
        }
    }

    console.warn("Value " + id + " not found")
    return;
}

function selectRoom(id) {
    console.info("Searching room " + id + " in " + DatamodelManager.datamodel.knownRooms.length + " known rooms")

    for (var i=0;i<DatamodelManager.datamodel.knownRooms.length;i++) {
        if (DatamodelManager.datamodel.knownRooms[i].id ===id) {
            return DatamodelManager.datamodel.knownRooms[i];
        }
    }

    console.warn("Known room " + id + " not found")
    return;
}

function value(v, undefinedValue) {
    return v===undefined ? undefinedValue : v
}

