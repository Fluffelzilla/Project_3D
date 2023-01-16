#include "Camera.h"

void Camera::MoveInDirection(float amount, const DirectX::XMFLOAT3& direction)
{
	position.x += direction.x * amount;
	position.y += direction.y * amount;
	position.z += direction.z * amount;
}

void Camera::RotateAroundAxis(float amount, const DirectX::XMFLOAT3& axis)
{
	DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&axis), amount);
}

Camera::Camera(ID3D11Device* device, const ProjectionInfo& projectionInfo, const DirectX::XMFLOAT3& initialPosition)
{
	Initialize(device, projectionInfo, initialPosition);
}

void Camera::Initialize(ID3D11Device* device, const ProjectionInfo& projectionInfo, const DirectX::XMFLOAT3& initialPosition)
{
	position = initialPosition;
	forward = DirectX::XMFLOAT3(0, 0, 1);
	up = DirectX::XMFLOAT3(0, 1, 0);
	right = DirectX::XMFLOAT3(1, 0, 0);

	projInfo.aspectRatio = projectionInfo.aspectRatio;
	projInfo.farZ = projectionInfo.farZ;
	projInfo.fovAngleY = projectionInfo.fovAngleY;
	projInfo.nearZ = projectionInfo.nearZ;

	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&forward), DirectX::XMLoadFloat3(&up));
	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(projInfo.fovAngleY, projInfo.aspectRatio, projInfo.nearZ, projInfo.farZ);
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	DirectX::XMMATRIX rotationY = DirectX::XMMatrixRotationY(0);

	matrixInfo.viewPro = DirectX::XMMatrixMultiplyTranspose(view, projection);
	matrixInfo.cPosition = position;
	matrixInfo.world = DirectX::XMMatrixMultiply(translation, rotationY);


	cameraBuffer.Initialize(device, cameraBuffer.GetSize());
}

void Camera::MoveForward(float amount)
{
	MoveInDirection(amount,forward);
}

void Camera::MoveRight(float amount)
{
	MoveInDirection(amount, right);
}

void Camera::MoveUp(float amount)
{
	MoveInDirection(amount, up);
}

void Camera::RotateForward(float amount)
{
	RotateAroundAxis(amount, forward);
	//DirectX::XMMatrixRotationZ(amount);
}

void Camera::RotateRight(float amount)
{
	RotateAroundAxis(amount, right);
	//DirectX::XMMatrixRotationY(amount);
}

void Camera::RotateUp(float amount)
{
	RotateAroundAxis(amount, up);
	//DirectX::XMMatrixRotationX(amount);
}

const DirectX::XMFLOAT3& Camera::GetPosition() const
{
	return position;
}

const DirectX::XMFLOAT3& Camera::GetForward() const
{
	return forward;
}

const DirectX::XMFLOAT3& Camera::GetRight() const
{
	return right;
}

const DirectX::XMFLOAT3& Camera::GetUp() const
{
	return up;
}

void Camera::UpdateInternalConstantBuffer(ID3D11DeviceContext* context)
{
	//TODO: check if matrixInfo contains correkt info!!
	cameraBuffer.UpdateBuffer(context, &matrixInfo);
}

ID3D11Buffer* Camera::GetConstantBuffer() const
{
	return cameraBuffer.GetBuffer();
}

DirectX::XMFLOAT4X4 Camera::GetViewProjectionMatrix() const
{
	DirectX::XMFLOAT4X4 temp;
	DirectX::XMStoreFloat4x4(&temp,matrixInfo.viewPro);
	return temp;
}
