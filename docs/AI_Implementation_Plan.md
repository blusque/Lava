# PyTorch + EnTT AI Implementation Plan for Lava Engine

## Updated Implementation Strategy

### Key Changes Made:
1. **TensorFlow → PyTorch**: Converted all neural network infrastructure to use LibTorch (PyTorch C++)
2. **Custom ECS → EnTT**: Adapted all AI systems to work with your existing EnTT integration
3. **Component Simplification**: AI components are now simple structs compatible with EnTT

## Phase 1: Core Infrastructure Setup (Months 1-3)

### 1.1 LibTorch Integration

#### Build System Updates (premake5.lua)
```lua
-- Add LibTorch to your premake5.lua
IncludeDirs["LibTorch"] = "Lava/vendor/libtorch/include"
IncludeDirs["LibTorchCuda"] = "Lava/vendor/libtorch/include/torch/csrc/api/include"

project "Lava"
    -- ...existing code...
    
    defines {
        "LAVA_USE_LIBTORCH" -- Enable PyTorch integration
    }
    
    includedirs {
        "%{IncludeDirs.LibTorch}",
        "%{IncludeDirs.LibTorchCuda}"
    }
    
    libdirs {
        "Lava/vendor/libtorch/lib"
    }
    
    links {
        "torch",
        "torch_cpu", 
        "c10",
        "torch_cuda" -- Optional for GPU support
    }
```

#### Installation Steps
1. Download LibTorch from pytorch.org (C++/Java package)
2. Extract to `Lava/vendor/libtorch/`
3. Update premake5.lua as shown above
4. Regenerate project files: `GenerateProject.bat`

### 1.2 EnTT Integration Enhancement

#### Existing EnTT + AI Components
Your existing EnTT system will now support AI components:

```cpp
// In your Scene class or wherever you manage entities
#include "Lava/AI/AIComponents.h"
#include "Lava/AI/AISystems.h"

// Create an AI character
auto aiCharacter = registry.create();
registry.emplace<TransformComponent>(aiCharacter);
registry.emplace<Lava::AI::NeuralAnimationComponent>(aiCharacter);

// Set up PFNN model
auto& neural = registry.get<Lava::AI::NeuralAnimationComponent>(aiCharacter);
neural.pfnnModel = Lava::AI::AI::GetModel("pfnn_locomotion");
neural.targetVelocity = {1.0f, 0.0f, 0.0f}; // Walk forward
```

### 1.3 Third-Party Library Integration Strategy

#### OGRE 3D Integration Plan
```cpp
// OGRE integration with existing Lava renderer
class OgreRenderer : public Lava::Renderer {
public:
    void Initialize() override {
        // Initialize OGRE alongside existing OpenGL renderer
        InitializeOgre();
        CreateBridge();
    }
    
    void RenderAICharacters(entt::registry& registry) {
        // Render characters with neural animation
        auto view = registry.view<NeuralAnimationComponent, TransformComponent>();
        for (auto entity : view) {
            auto& neural = view.get<NeuralAnimationComponent>(entity);
            auto& transform = view.get<TransformComponent>(entity);
            
            // Convert neural animation to OGRE scene nodes
            UpdateOgreFromNeuralAnimation(entity, neural, transform);
        }
    }
};
```

#### RayGUI Integration
```cpp
// RayGUI for game UI, ImGui for editor
#include "raygui.h"

class GameUI {
public:
    void RenderAIControls(entt::registry& registry) {
        auto view = registry.view<NeuralAnimationComponent>();
        for (auto entity : view) {
            auto& neural = view.get<NeuralAnimationComponent>(entity);
            
            // RayGUI controls for AI parameters
            neural.phaseFrequency = GuiSlider({10, 10, 200, 20}, "Speed", 
                                            neural.phaseFrequency, 0.5f, 3.0f);
            
            if (GuiButton({10, 40, 100, 30}, "Reset Animation")) {
                // Reset neural animation state
            }
        }
    }
};
```

## Phase 2: PFNN Implementation (Months 4-6)

### 2.1 PyTorch Model Setup

#### Model Training (Python)
```python
# train_pfnn.py - PyTorch PFNN training script
import torch
import torch.nn as nn

class PFNN(nn.Module):
    def __init__(self, input_size=342, output_size=311):
        super(PFNN, self).__init__()
        self.phase_layers = nn.ModuleList([
            nn.Linear(input_size, 512),
            nn.Linear(512, 512),
            nn.Linear(512, output_size)
        ])
    
    def forward(self, x, phase):
        # Phase-functioned neural network forward pass
        for layer in self.phase_layers:
            x = torch.relu(layer(x))
        return x

# Train and export to TorchScript
model = PFNN()
traced_model = torch.jit.trace(model, (torch.randn(1, 342), torch.randn(1, 1)))
traced_model.save("assets/models/pfnn_locomotion.pt")
```

#### C++ Integration
```cpp
// Using the PyTorch model in C++
void PFNNLocomotionSystem::Initialize() {
    // Load the trained PyTorch model
    sharedPFNNModel = std::make_shared<TorchInference>();
    sharedPFNNModel->LoadModel("assets/models/pfnn_locomotion.pt");
    sharedPFNNModel->SetDevice(true); // Use GPU if available
}

void PFNNLocomotionSystem::Update(float deltaTime, entt::registry& registry) {
    auto view = registry.view<NeuralAnimationComponent, TransformComponent>();
    
    // Batch process entities for better performance
    std::vector<entt::entity> entities;
    std::vector<std::vector<float>> inputs;
    
    for (auto entity : view) {
        auto& neural = view.get<NeuralAnimationComponent>(entity);
        auto& transform = view.get<TransformComponent>(entity);
        
        // Prepare input for neural network
        auto input = PrepareNetworkInput(neural, transform);
        entities.push_back(entity);
        inputs.push_back(input);
    }
    
    // Batch inference
    if (!inputs.empty()) {
        auto outputs = sharedPFNNModel->BatchInference(inputs);
        
        // Apply results
        for (size_t i = 0; i < entities.size(); ++i) {
            ApplyNetworkOutput(entities[i], outputs[i], registry);
        }
    }
}
```

## Phase 3: AIGC Integration (Months 7-9)

### 3.1 AI Content Generation Pipeline

#### Texture Generation
```python
# texture_generator.py - PyTorch-based texture generation
import torch
from diffusers import StableDiffusionPipeline

class TextureGenerator:
    def __init__(self):
        self.pipeline = StableDiffusionPipeline.from_pretrained(
            "runwayml/stable-diffusion-v1-5",
            torch_dtype=torch.float16
        )
    
    def generate_texture(self, prompt, size=512):
        image = self.pipeline(prompt, height=size, width=size).images[0]
        return image

# Export for C++ usage
generator = TextureGenerator()
traced = torch.jit.trace(generator.pipeline.unet, example_input)
traced.save("assets/models/texture_generator.pt")
```

#### C++ Integration
```cpp
void AIGCSystem::RequestTextureGeneration(entt::entity entity, 
                                        const std::string& prompt,
                                        const std::unordered_map<std::string, float>& params) {
    auto& aigc = registry.get<AIGCComponent>(entity);
    
    AIGCComponent::GenerationRequest request;
    request.type = AIGCComponent::GenerationRequest::TEXTURE;
    request.prompt = prompt;
    request.parameters = params;
    
    aigc.requestQueue.push(request);
}
```

## Practical Implementation Steps

### Week 1-2: Setup
1. **Download LibTorch**: Get the C++ distribution from pytorch.org
2. **Update Build System**: Modify premake5.lua to include LibTorch
3. **Test Basic Integration**: Create a simple PyTorch inference test

### Week 3-4: Core AI Framework
1. **Add AI Headers**: Copy the AI header files I created into your project
2. **Initialize AI Subsystem**: Add AI::Initialize() to your Application::OnBegin()
3. **Create Test Scene**: Add a character with NeuralAnimationComponent

### Month 2: PFNN Development
1. **Train Basic Model**: Use PyTorch to train a simple locomotion model
2. **C++ Integration**: Load and run inference in real-time
3. **Performance Optimization**: Batch processing and GPU acceleration

### Month 3: Advanced Features
1. **OGRE Integration**: Begin renderer integration planning
2. **Motion Capture**: Add webcam-based pose estimation
3. **Content Generation**: Basic texture generation pipeline

## Success Metrics

### Technical Benchmarks
- [ ] PyTorch model loading and inference working
- [ ] Real-time PFNN at 60fps for 5+ characters
- [ ] EnTT integration with AI components functional
- [ ] GPU acceleration working (if available)

### Feature Milestones
- [ ] Character walks using neural network
- [ ] Basic texture generation from text prompts
- [ ] Motion capture from webcam
- [ ] OGRE rendering pipeline integrated

## Hardware Requirements

### Development Setup
- **GPU**: RTX 3060 or better for training and inference
- **RAM**: 16GB+ for model loading and processing
- **Storage**: 50GB+ for models and datasets
- **CPU**: Modern multi-core for real-time processing

### Model Storage Structure
```
assets/
└── models/
    ├── pfnn_locomotion.pt          # Main locomotion model
    ├── deepmimic_humanoid.pt       # Physics-based learning
    ├── texture_generator.pt        # AI texture generation
    ├── pose_estimation.pt          # Motion capture
    └── style_transfer.pt           # Style transfer
```

## Risk Mitigation

### Technical Risks
1. **PyTorch C++ Complexity**: Start with simple models, gradually increase complexity
2. **Performance**: Profile early, optimize incrementally
3. **Memory Usage**: Implement model streaming and compression
4. **GPU Compatibility**: Have CPU fallbacks for all operations

### Practical Solutions
1. **Use Pre-trained Models**: Start with existing models before training custom ones
2. **Community Resources**: Leverage PyTorch community and examples
3. **Incremental Development**: Build one feature at a time
4. **Fallback Systems**: Traditional animation as backup

This updated plan focuses on practical implementation using proven technologies (PyTorch + EnTT) while maintaining your vision of cutting-edge AI animation features.
