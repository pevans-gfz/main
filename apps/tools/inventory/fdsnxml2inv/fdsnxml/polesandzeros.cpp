/***************************************************************************
 * Copyright (C) gempa GmbH                                                *
 * Contact: gempa GmbH (seiscomp-dev@gempa.de)                             *
 *                                                                         *
 * This file may be used under the terms of the GNU Affero                 *
 * Public License version 3.0 as published by the Free Software Foundation *
 * and appearing in the file LICENSE included in the packaging of this     *
 * file. Please review the following information to ensure the GNU Affero  *
 * Public License version 3.0 requirements will be met:                    *
 * https://www.gnu.org/licenses/agpl-3.0.html.                             *
 ***************************************************************************/


#define SEISCOMP_COMPONENT SWE
#include <fdsnxml/polesandzeros.h>
#include <fdsnxml/poleandzero.h>
#include <fdsnxml/poleandzero.h>
#include <algorithm>
#include <seiscomp/logging/log.h>


namespace Seiscomp {
namespace FDSNXML {


namespace {

static Seiscomp::Core::MetaEnumImpl<PzTransferFunctionType> metaPzTransferFunctionType;

}


PolesAndZeros::MetaObject::MetaObject(const Core::RTTI *rtti, const Core::MetaObject *base) : Core::MetaObject(rtti, base) {
	addProperty(enumProperty("PzTransferFunctionType", "PzTransferFunctionType", false, false, &metaPzTransferFunctionType, &PolesAndZeros::setPzTransferFunctionType, &PolesAndZeros::pzTransferFunctionType));
	addProperty(Core::simpleProperty("NormalizationFactor", "float", false, false, false, false, false, false, NULL, &PolesAndZeros::setNormalizationFactor, &PolesAndZeros::normalizationFactor));
	addProperty(objectProperty<FrequencyType>("NormalizationFrequency", "FDSNXML::FrequencyType", false, false, &PolesAndZeros::setNormalizationFrequency, &PolesAndZeros::normalizationFrequency));
	addProperty(arrayClassProperty<PoleAndZero>("Zero", "FDSNXML::PoleAndZero", &PolesAndZeros::zeroCount, &PolesAndZeros::zero, static_cast<bool (PolesAndZeros::*)(PoleAndZero*)>(&PolesAndZeros::addZero), &PolesAndZeros::removeZero, static_cast<bool (PolesAndZeros::*)(PoleAndZero*)>(&PolesAndZeros::removeZero)));
	addProperty(arrayClassProperty<PoleAndZero>("Pole", "FDSNXML::PoleAndZero", &PolesAndZeros::poleCount, &PolesAndZeros::pole, static_cast<bool (PolesAndZeros::*)(PoleAndZero*)>(&PolesAndZeros::addPole), &PolesAndZeros::removePole, static_cast<bool (PolesAndZeros::*)(PoleAndZero*)>(&PolesAndZeros::removePole)));
}


IMPLEMENT_RTTI(PolesAndZeros, "FDSNXML::PolesAndZeros", BaseFilter)
IMPLEMENT_RTTI_METHODS(PolesAndZeros)
IMPLEMENT_METAOBJECT_DERIVED(PolesAndZeros, BaseFilter)


PolesAndZeros::PolesAndZeros() {
	_normalizationFactor = 0;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PolesAndZeros::PolesAndZeros(const PolesAndZeros &other)
 : BaseFilter() {
	*this = other;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PolesAndZeros::~PolesAndZeros() {}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool PolesAndZeros::operator==(const PolesAndZeros &rhs) const {
	if ( !(_pzTransferFunctionType == rhs._pzTransferFunctionType) )
		return false;
	if ( !(_normalizationFactor == rhs._normalizationFactor) )
		return false;
	if ( !(_normalizationFrequency == rhs._normalizationFrequency) )
		return false;
	return true;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void PolesAndZeros::setPzTransferFunctionType(PzTransferFunctionType pzTransferFunctionType) {
	_pzTransferFunctionType = pzTransferFunctionType;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PzTransferFunctionType PolesAndZeros::pzTransferFunctionType() const {
	return _pzTransferFunctionType;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void PolesAndZeros::setNormalizationFactor(double normalizationFactor) {
	_normalizationFactor = normalizationFactor;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
double PolesAndZeros::normalizationFactor() const {
	return _normalizationFactor;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void PolesAndZeros::setNormalizationFrequency(const FrequencyType& normalizationFrequency) {
	_normalizationFrequency = normalizationFrequency;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FrequencyType& PolesAndZeros::normalizationFrequency() {
	return _normalizationFrequency;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
const FrequencyType& PolesAndZeros::normalizationFrequency() const {
	return _normalizationFrequency;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PolesAndZeros& PolesAndZeros::operator=(const PolesAndZeros &other) {
	BaseFilter::operator=(other);
	_pzTransferFunctionType = other._pzTransferFunctionType;
	_normalizationFactor = other._normalizationFactor;
	_normalizationFrequency = other._normalizationFrequency;
	return *this;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
size_t PolesAndZeros::zeroCount() const {
	return _zeros.size();
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PoleAndZero* PolesAndZeros::zero(size_t i) const {
	return _zeros[i].get();
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool PolesAndZeros::addZero(PoleAndZero *obj) {
	if ( obj == NULL )
		return false;

	// Add the element
	_zeros.push_back(obj);
	
	return true;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool PolesAndZeros::removeZero(PoleAndZero *obj) {
	if ( obj == NULL )
		return false;

	std::vector<PoleAndZeroPtr>::iterator it;
	it = std::find(_zeros.begin(), _zeros.end(), obj);
	// Element has not been found
	if ( it == _zeros.end() ) {
		SEISCOMP_ERROR("PolesAndZeros::removeZero(PoleAndZero*) -> child object has not been found although the parent pointer matches???");
		return false;
	}

	return true;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool PolesAndZeros::removeZero(size_t i) {
	// index out of bounds
	if ( i >= _zeros.size() )
		return false;

	_zeros.erase(_zeros.begin() + i);

	return true;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
size_t PolesAndZeros::poleCount() const {
	return _poles.size();
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PoleAndZero* PolesAndZeros::pole(size_t i) const {
	return _poles[i].get();
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool PolesAndZeros::addPole(PoleAndZero *obj) {
	if ( obj == NULL )
		return false;

	// Add the element
	_poles.push_back(obj);
	
	return true;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool PolesAndZeros::removePole(PoleAndZero *obj) {
	if ( obj == NULL )
		return false;

	std::vector<PoleAndZeroPtr>::iterator it;
	it = std::find(_poles.begin(), _poles.end(), obj);
	// Element has not been found
	if ( it == _poles.end() ) {
		SEISCOMP_ERROR("PolesAndZeros::removePole(PoleAndZero*) -> child object has not been found although the parent pointer matches???");
		return false;
	}

	return true;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool PolesAndZeros::removePole(size_t i) {
	// index out of bounds
	if ( i >= _poles.size() )
		return false;

	_poles.erase(_poles.begin() + i);

	return true;
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
}
