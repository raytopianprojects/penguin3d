/**
 * PANDA 3D SOFTWARE
 * Copyright (c) Carnegie Mellon University.  All rights reserved.
 *
 * All use of this software is subject to the terms of the revised BSD
 * license.  You should have received a copy of this license along
 * with this source code in a file named "LICENSE."
 *
 * @file assimpLoader.h
 * @author rdb
 * @date 2011-03-29
 */

#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include "config_assimp.h"
#include "filename.h"
#include "modelRoot.h"
#include "texture.h"
#include "textureStage.h"
#include "pmap.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

class Character;
class CharacterJointBundle;
class PartGroup;
class AnimBundle;
class AnimGroup;

struct char_cmp {
  bool operator () (const char *a, const char *b) const {
    return strcmp(a,b) < 0;
  }
};
typedef pmap<const char *, const aiNode *, char_cmp> BoneMap;
typedef pmap<const char *, PT(Character), char_cmp> CharacterMap;

/**
 * Class that interfaces with Assimp and builds Panda nodes to represent the
 * Assimp structures.  The loader should be reusable.
 */
class AssimpLoader : public TypedReferenceCount {
public:
  AssimpLoader();
  virtual ~AssimpLoader();

  void get_extensions(std::string &ext) const;

  bool read(const Filename &filename);
  void build_graph();

public:
  bool _error;
  PT(ModelRoot) _root;
  Filename _filename;
  Mutex _lock;

private:
  Assimp::Importer _importer;
  const aiScene *_scene;

  struct Geoms {
    PT(Geom) _points;
    PT(Geom) _lines;
    PT(Geom) _triangles;
    unsigned int _mat_index = 0;
  };

  // These arrays are temporarily used during the build_graph run.
  PT(Texture) *_textures;
  CPT(RenderState) *_mat_states;
  Geoms *_geoms;
  BoneMap _bonemap;
  CharacterMap _charmap;

  const aiNode *find_node(const aiNode &root, const aiString &name);

  void load_texture(size_t index);
  void load_texture_stage(const aiMaterial &mat, const aiTextureType &ttype,
                          TextureStage::Mode mode, CPT(TextureAttrib) &tattr,
                          CPT(TexMatrixAttrib) &tmattr);
  void load_material(size_t index);
  void create_joint(Character *character, CharacterJointBundle *bundle, PartGroup *parent, const aiNode &node);
  void create_anim_channel(const aiAnimation &anim, AnimBundle *bundle, AnimGroup *parent, const aiNode &node);
  void load_mesh(size_t index);
  void load_node(const aiNode &node, PandaNode *parent);
  void load_light(const aiLight &light);
};

#include "assimpLoader.I"

#endif
