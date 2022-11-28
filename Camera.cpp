#include "Camera.h"

void Camera::MoveInDirection(float amount, const DirectX::XMFLOAT3& direction)
{
	position.x += direction.x * amount;
	position.y += direction.y * amount;
	position.z += direction.z * amount;
}

void Camera::RotateAroundAxis(float amount, const DirectX::XMFLOAT3& axis)
{

}

Camera::Camera(ID3D11Device* device, const ProjectionInfo& projectionInfo, const DirectX::XMFLOAT3& initialPosition)
{
	projInfo.aspectRatio = projectionInfo.aspectRatio;
	projInfo.farZ = projectionInfo.farZ;
	projInfo.fovAngleY = projectionInfo.fovAngleY;
	projInfo.nearZ = projectionInfo.nearZ;

	Initialize(device, projectionInfo, initialPosition);
}

void Camera::Initialize(ID3D11Device* device, const ProjectionInfo& projectionInfo, const DirectX::XMFLOAT3& initialPosition)
{
	cameraBuffer.Initialize(device, cameraBuffer.GetSize());

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(cameraBuffer.GetSize());
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	//device->CreateBuffer(&bufferDesc, NULL, &cameraBuffer.GetBuffer())
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
	
}

void Camera::RotateRight(float amount)
{
}

void Camera::RotateUp(float amount)
{
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
	return right;
}

void Camera::UpdateInternalConstantBuffer(ID3D11DeviceContext* context)
{
	//matrixInfo* dataptr;

	//D3D11_MAPPED_SUBRESOURCE mappedResource;
	////fill mappedResource whit zero values, second input is the amound to set to zero
	//ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//context->Map(cameraBuffer.GetBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	////get a pointer to the data contained in a subresource, and denies the GPU access to that subresource

	//dataptr = (matrixInfo*)mappedResource.pData;
	//dataptr->world = DirectX::XMMatrixTranspose(mainCamera.getWorld());
	//dataptr->viewPro = mainCamera.getViewProjection();
	//dataptr->cPosition = mainCamera.getCameraPosition();
	////new data input in CPU

	//context->Unmap(cameraBuffer.GetBuffer(), 0);
	////Lock new data att CPU and give acces back to the GPU

	//context->VSSetConstantBuffers(0, 1, &cameraBuffer.GetBuffer());
}

ID3D11Buffer* Camera::GetConstantBuffer() const
{
	return nullptr;
}

DirectX::XMFLOAT4X4 Camera::GetViewProjectionMatrix() const
{
	return DirectX::XMFLOAT4X4();
}
