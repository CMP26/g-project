#pragma once

#include <asset-loader.hpp>
#include <ecs/world.hpp>
#include <components/camera.hpp>
#include <components/mesh-renderer.hpp>
#include <application.hpp>

// This is a helper function that will search for a component and will return the first one found
template<typename T>
T* find(our::World *world){
    for(auto& entity : world->getEntities()){
        T* component = entity->getComponent<T>();
        if(component) return component;
    }
    return nullptr;
}

// This state tests and shows how to use the ECS framework and deserialization.
class EntityTestState: public our::State {

    our::World world;
    
    void onInitialize() override {
        // First of all, we get the scene configuration from the app config
        auto& config = getApp()->getConfig()["scene"];
        // If we have assets in the scene config, we deserialize them
        if(config.contains("assets")){
            our::deserializeAllAssets(config["assets"]);
        }

        // If we have a world in the scene config, we use it to populate our world
        if(config.contains("world")){
            world.deserialize(config["world"]);
        }
        
    }

    // void onDraw(double deltaTime) override {
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //     // First, we look for a camera and if none was found, we return (there is nothing we can render)
    //     our::CameraComponent* camera = find<our::CameraComponent>(&world);
    //     if(camera == nullptr) return;

    //     // Then we compute the VP matrix from the camera
    //     glm::ivec2 size = getApp()->getFrameBufferSize();
    //     //TODO: (Req 8) Change the following line to compute the correct view projection matrix     DONE
    //     glm::mat4 VP = camera->getProjectionMatrix(size) * camera->getViewMatrix();

    //     for(auto& entity : world.getEntities()){
    //         // For each entity, we look for a mesh renderer (if none was found, we skip this entity)
    //         our::MeshRendererComponent* meshRenderer = entity->getComponent<our::MeshRendererComponent>();
    //         if(meshRenderer == nullptr) continue;
    //         //TODO: (Req 8) Complete the loop body to draw the current entity
    //         // Then we setup the material, send the transform matrix to the shader then draw the mesh

    //         if(meshRenderer->material) meshRenderer->material->setup();
    //         auto shader = meshRenderer->material->shader;
    //         glm::mat4 matrix = VP * entity->getLocalToWorldMatrix();
    //         if(shader) {
    //             shader->set("transform", matrix);
    //         }
    //         if(meshRenderer->mesh) meshRenderer->mesh->draw();
    //     }
    // }

    void onDraw(double deltaTime) override {
        // Clear the screen and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        // Find the main camera in the world
        our::CameraComponent* camera = find<our::CameraComponent>(&world);
        if(camera == nullptr) return; // Nothing to render without a camera
    
        // Compute the View-Projection matrix using the framebuffer size
        glm::ivec2 size = getApp()->getFrameBufferSize();
        glm::mat4 VP = camera->getProjectionMatrix(size) * camera->getViewMatrix();
    
        // Loop through all entities in the world
        for(auto& entity : world.getEntities()){
            // Skip entities without a MeshRendererComponent
            auto* meshRenderer = entity->getComponent<our::MeshRendererComponent>();
            if(!meshRenderer) continue;
    
            // Setup the material
            if(meshRenderer->material) {
                meshRenderer->material->setup();
    
                // Compute the model-to-world transformation matrix
                glm::mat4 M = entity->getLocalToWorldMatrix();
                glm::mat4 transform = VP * M;
    
                // Send the final transform matrix to the shader
                if(meshRenderer->material->shader)
                    meshRenderer->material->shader->set("transform", transform);
            }
    
            // Draw the mesh
            if(meshRenderer->mesh)
                meshRenderer->mesh->draw();
        }
    }
    
    void onDestroy() override {
        world.clear();
        our::clearAllAssets();
    }
};