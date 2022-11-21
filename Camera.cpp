#include "Camera.h"

void Camera::MoveInDirection(float amount, const DirectX::XMFLOAT3& direction)
{
}

void Camera::RotateAroundAxis(float amount, const DirectX::XMFLOAT3& axis)
{
}

Camera::Camera(ID3D11Device* device, const ProjectionInfo& projectionInfo, const DirectX::XMFLOAT3& initialPosition)
{
}

void Camera::Initialize(ID3D11Device* device, const ProjectionInfo& projectionInfo, const DirectX::XMFLOAT3& initialPosition)
{
}

void Camera::MoveForward(float amount)
{
}

void Camera::MoveRight(float amount)
{
}

void Camera::MoveUp(float amount)
{
}

void Camera::RotateForward(float amount)
{
}

void Camera::RotateRight(float amount)
{
}

void Camera::RotateUp(float amount)
{
}

const DirectX::XMFLOAT3& Camera::GetPosition() const
{
	// // O: insert return statement here
}

const DirectX::XMFLOAT3& Camera::GetForward() const
{
	// // O: insert return statement here
}

const DirectX::XMFLOAT3& Camera::GetRight() const
{
	// // O: insert return statement here
}

const DirectX::XMFLOAT3& Camera::GetUp() const
{
	// // O: insert return statement here
}

void Camera::UpdateInternalConstantBuffer(ID3D11DeviceContext* context)
{
}

ID3D11Buffer* Camera::GetConstantBuffer() const
{
	return nullptr;
}

DirectX::XMFLOAT4X4 Camera::GetViewProjectionMatrix() const
{
	return DirectX::XMFLOAT4X4();
}
