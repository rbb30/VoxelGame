#include "raylib.h"
#include "raymath.h"

const Vector3 forward = Vector3 { 0.0f, 0.0f, -1.0f };

class Player {
    public:
        Player();
        Camera GetCamera();
        void MoveCamera();
    protected:
        Camera _camera;
        float _cameraYaw;
        float _cameraPitch;
        float _cameraMoveSpeed;
};
