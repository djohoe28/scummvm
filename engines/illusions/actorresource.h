/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ILLUSIONS_ACTORRESOURCE_H
#define ILLUSIONS_ACTORRESOURCE_H

#include "illusions/graphics.h"
#include "illusions/resourcesystem.h"
#include "graphics/surface.h"

namespace Illusions {

class IllusionsEngine;

class ActorResourceLoader : public BaseResourceLoader {
public:
	ActorResourceLoader(IllusionsEngine *vm) : _vm(vm) {}
	virtual ~ActorResourceLoader() {}
	virtual void load(Resource *resource);
	virtual void unload(Resource *resource);
	virtual void buildFilename(Resource *resource);
	virtual bool isFlag(int flag);
protected:
	IllusionsEngine *_vm;
};

struct Frame {
	//field_0 dd
	// TODO config dd
	uint32 _pixelSize;
	WidthHeight _dimensions;
	byte *_compressedPixels;
	void load(byte *dataStart, Common::SeekableReadStream &stream);
};

struct Sequence {
	uint32 _sequenceId;
	uint32 _unk4;
	byte *_sequenceCode;
	void load(byte *dataStart, Common::SeekableReadStream &stream);
};

struct ActorType {
	uint32 _actorTypeId;
	SurfInfo _surfInfo;
	// TODO config dd
	// TODO namedPointsCount dw
	// TODO namedPoints dd
	RGB _color;
	byte _scale;
	byte _priority;
	int16 _value1E;
	uint16 _bgItem28sIndex;
	uint16 _bgItem22sIndex;
	uint16 _bgItem30sIndex;
	uint16 _bgItem26sIndex;
	uint16 _bgItem38sIndex;
	uint16 _flags;
	void load(byte *dataStart, Common::SeekableReadStream &stream);
};

class ActorResource {
public:
	ActorResource();
	~ActorResource();
	void load(byte *data, uint32 dataSize);
public:
	uint32 _totalSize;
	Common::Array<ActorType> _actorTypes;
	Common::Array<Sequence> _sequences;
	Common::Array<Frame> _frames;
};

class ActorItem {
public:
	ActorItem();
	~ActorItem();
	void pause();
	void unpause();
public:
	uint32 _tag;
	int _pauseCtr;
	ActorResource *_actRes;
};

class ActorItems {
public:
	ActorItems(IllusionsEngine *vm);
	~ActorItems();
	ActorItem *allocActorItem();
	void pauseByTag(uint32 tag);
	void unpauseByTag(uint32 tag);
protected:
	typedef Common::List<ActorItem*> Items;
	typedef Items::iterator ItemsIterator;
	IllusionsEngine *_vm;
	Items _items;
};

} // End of namespace Illusions

#endif // ILLUSIONS_ACTORRESOURCE_H