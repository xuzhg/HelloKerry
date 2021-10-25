#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer() :
    m_buffer(nullptr),
    m_layout(nullptr)
{
    m_size_vertex = 0;
    m_size_list = 0;
}

VertexBuffer::~VertexBuffer()
{
}

UINT VertexBuffer::getSizeVertexList()
{
    return this->m_size_list;
}

bool VertexBuffer::load(void* list_vertics, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
    if (m_buffer)
        m_buffer->Release();

    if (m_layout)
        m_layout->Release();

    D3D11_BUFFER_DESC buff_desc = {};
    buff_desc.Usage = D3D11_USAGE_DEFAULT;
    buff_desc.ByteWidth = size_vertex * size_list;
    buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buff_desc.CPUAccessFlags = 0;
    buff_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_vertics;
    m_size_vertex = size_vertex;
    m_size_list = size_list;

    HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer);
    if (FAILED(hr))
    {
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    UINT size_layout = ARRAYSIZE(layout);

    hr = GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout);
    if(FAILED(hr))
    {
        return false;
    }
    return true;
}

bool VertexBuffer::release()
{
    m_buffer->Release();
    m_layout->Release();
    delete this;
    return true;
}
