// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <Common/MemoryInputStream.h>
#include <Common/StringTools.h>
#include <Common/VectorOutputStream.h>

#include <config/CryptoNoteConfig.h>
#include <config/Constants.h>

#include <limits>

#include <Serialization/BinaryOutputStreamSerializer.h>
#include <Serialization/BinaryInputStreamSerializer.h>
#include <Serialization/CryptoNoteSerialization.h>
#include <Serialization/SerializationTools.h>

namespace CryptoNote {

void getBinaryArrayHash(const BinaryArray& binaryArray, Crypto::Hash& hash);
Crypto::Hash getBinaryArrayHash(const BinaryArray& binaryArray);

template<class T>
bool getObjectBinarySize(const T& object, size_t& size) {
  BinaryArray ba;
  if (!toBinaryArray(object, ba)) {
    size = (std::numeric_limits<size_t>::max)();
    return false;
  }

  size = ba.size();
  return true;
}

template<class T>
size_t getObjectBinarySize(const T& object) {
  size_t size;
  getObjectBinarySize(object, size);
  return size;
}

template<class T>
bool getObjectHash(const T& object, Crypto::Hash& hash) {
  BinaryArray ba;
  if (!toBinaryArray(object, ba)) {
    hash = Constants::NULL_HASH;
    return false;
  }

  hash = getBinaryArrayHash(ba);
  return true;
}

template<class T>
bool getObjectHash(const T& object, Crypto::Hash& hash, size_t& size) {
  BinaryArray ba;
  if (!toBinaryArray(object, ba)) {
    hash = Constants::NULL_HASH;
    size = (std::numeric_limits<size_t>::max)();
    return false;
  }

  size = ba.size();
  hash = getBinaryArrayHash(ba);
  return true;
}

template<class T>
Crypto::Hash getObjectHash(const T& object) {
  Crypto::Hash hash;
  getObjectHash(object, hash);
  return hash;
}

inline bool getBaseTransactionHash(const BaseTransaction& tx, Crypto::Hash& hash) {
  return getObjectHash(tx, hash);
}

}
