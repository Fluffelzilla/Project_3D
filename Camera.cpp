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
	//:cameraBuffer(device, sizeof(MatrixInfo), &matrixInfo)
{
	Initialize(device, projectionInfo, initialPosition);
}

Camera::~Camera()
{
	if (cameraBuffer)
	{
		cameraBuffer->Release();
		cameraBuffer = nullptr;
	}
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

	InitializeBuffer(device);
}

void Camera::InitializeBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(MatrixInfo);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &matrixInfo;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateBuffer(&bufferDesc, NULL, &cameraBuffer);
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
	
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&forward), DirectX::XMLoadFloat3(&up));

	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(projInfo.fovAngleY, projInfo.aspectRatio, projInfo.nearZ, projInfo.farZ);
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(0, 0, 0); // this is object world space not camera!!!!
	DirectX::XMMATRIX rotationY = DirectX::XMMatrixRotationY(0);//this dont belonge here :´(

	matrixInfo.viewPro = DirectX::XMMatrixMultiplyTranspose(view, projection);
	matrixInfo.cPosition = position;
	matrixInfo.world = DirectX::XMMatrixMultiply(translation, rotationY);

	MatrixInfo* dataptr;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT hr = context->Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataptr = (MatrixInfo*)mappedResource.pData;
	dataptr->world = DirectX::XMMatrixTranspose(matrixInfo.world);
	dataptr->viewPro = matrixInfo.viewPro;
	dataptr->cPosition = matrixInfo.cPosition;
	context->Unmap(cameraBuffer, 0);

	context->VSSetConstantBuffers(0, 1, &cameraBuffer);
}

ID3D11Buffer* Camera::GetConstantBuffer() const
{
	return cameraBuffer;
}

DirectX::XMFLOAT4X4 Camera::GetViewProjectionMatrix() const
{
	DirectX::XMFLOAT4X4 temp;
	DirectX::XMStoreFloat4x4(&temp,matrixInfo.viewPro);
	return temp;
}
