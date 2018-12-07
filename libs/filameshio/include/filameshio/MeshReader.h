/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_FILAMENT_FILAMESHIO_MESHREADER_H
#define TNT_FILAMENT_FILAMESHIO_MESHREADER_H

#include <utils/Entity.h>
#include <utils/Path.h>

#include <map>
#include <string>

namespace filament {
    class Engine;
    class VertexBuffer;
    class IndexBuffer;
    class MaterialInstance;
}

/**
 * This API can be used to read meshes stored in the "filamesh" format produced
 * by the command line tool of the same name. This file format is documented in
 * "docs/filamesh.md" in the Filament distribution.
 */
class MeshReader {
public:
    using Callback = void(*)(void* buffer, size_t size, void* user);
    using MaterialRegistry = std::map<std::string, filament::MaterialInstance*>;

    struct Mesh {
        utils::Entity renderable;
        filament::VertexBuffer* vertexBuffer = nullptr;
        filament::IndexBuffer* indexBuffer = nullptr;
    };

    /**
     * Loads a filamesh renderable from the specified file. The material registry
     * can be used to provide named materials. If a material found in the filamesh
     * file cannot be matched to a material in the registry, a default material is
     * used instead. The default material can be overridden by adding a material
     * named "DefaultMaterial" to the registry.
     */
    static Mesh loadMeshFromFile(filament::Engine* engine,
            const utils::Path& path,
            const MaterialRegistry& materials);

    /**
     * Loads a filamesh renderable from an in-memory buffer. The material registry
     * can be used to provide named materials. If a material found in the filamesh
     * file cannot be matched to a material in the registry, a default material is
     * used instead. The default material can be overridden by adding a material
     * named "DefaultMaterial" to the registry.
     */
    static Mesh loadMeshFromBuffer(filament::Engine* engine,
            void const* data, Callback destructor, void* user,
            const MaterialRegistry& materials);

    /**
     * Loads a filamesh renderable from an in-memory buffer. The material registry
     * can be used to provide named materials. All the primitives of the decoded
     * renderable are assigned the specified default material.
     */
    static Mesh loadMeshFromBuffer(filament::Engine* engine,
            void const* data, Callback destructor, void* user,
            filament::MaterialInstance* defaultMaterial);
};

#endif // TNT_FILAMENT_FILAMESHIO_MESHREADER_H