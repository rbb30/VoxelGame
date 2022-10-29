#include "player.hpp"
#include "raymath.h"

#define CAMERA_PITCH_LIMIT (PI / 2.5f)
#define CAMERA_MOVE_SPEED_MIN   8.0f
#define CAMERA_MOVE_SPEED_MAX   64.0f
#define CAMERA_ACCELERATION     16.0f


Player::Player() {
    _camera = { 0 };
	_camera.up = Vector3 { 0.0f, 1.0f, 0.0f };;
	_camera.fovy = 70.0f;
	_camera.projection = CAMERA_PERSPECTIVE;
    _cameraMoveSpeed = CAMERA_MOVE_SPEED_MIN;
};

Camera Player::GetCamera() {
    return _camera;
}

void Player::MoveCamera()
{
    //Camera controls
    Vector3 cameraMovement = Vector3Zero();
    if (IsKeyDown(KEY_D))
    {
        cameraMovement.x = 1.0f;
    }
    else if (IsKeyDown(KEY_A))
    {
        cameraMovement.x = -1.0f;
    }

    if (IsKeyDown(KEY_W))
    {
        cameraMovement.z = -1.0f;
    }
    else if (IsKeyDown(KEY_S))
    {
        cameraMovement.z = 1.0f;
    }

    if (IsKeyDown(KEY_SPACE))
    {
        cameraMovement.y = 1.0f;
    }
    else if (IsKeyDown(KEY_C))
    {
        cameraMovement.y = -1.0f;
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S))
    {
        _cameraMoveSpeed += CAMERA_ACCELERATION * GetFrameTime();
    }
    else
    {
        _cameraMoveSpeed = CAMERA_MOVE_SPEED_MIN;
    }
    _cameraMoveSpeed = Clamp(_cameraMoveSpeed, CAMERA_MOVE_SPEED_MIN, CAMERA_MOVE_SPEED_MAX);

    // Free movement of camera
    _cameraYaw -= GetMouseDelta().x * GetFrameTime();
    _cameraPitch -= GetMouseDelta().y * GetFrameTime();
    _cameraPitch = Clamp(_cameraPitch, -CAMERA_PITCH_LIMIT, CAMERA_PITCH_LIMIT);


    cameraMovement = Vector3Scale(Vector3Normalize(cameraMovement), _cameraMoveSpeed * GetFrameTime());
    Matrix cameraRotation = MatrixMultiply(MatrixRotateX(_cameraPitch), MatrixRotateY(_cameraYaw));
    Vector3 rotatedMovement = Vector3Transform(cameraMovement, cameraRotation);

    _camera.position = Vector3Add(_camera.position, rotatedMovement);
    _camera.target = Vector3Add(_camera.position, Vector3Transform(forward, cameraRotation));
}