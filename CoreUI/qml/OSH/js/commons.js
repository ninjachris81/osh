var invalidValue = "";

function formatValue(v) {
    return v.rawValue === undefined ? invalidValue : v.rawValue + " " + v.unitTypeSuffix
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

function searchIndex(id, coll) {
    for (var i=0;i<coll.length;i++) {
        if (coll[i].fullId ===id) {
            return i;
        }
    }
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

function value(v, undefinedValue) {
    return v===undefined ? undefinedValue : v
}
