#pragma once

template<typename T, typename N>
class FIFO
{
public:
	FIFO(T *data, N size) noexcept:
		m_Data(data), m_Size(size)
	{}

	bool write(T val) noexcept
	{
		if ((m_Write + 1) % m_Size == m_Read) return false;

		m_Data[m_Write] = val;
		m_Write = (m_Write + 1) % m_Size;

		return true;
	}

	bool empty(void)
	{
		return (m_Read == m_Write);
	}

	T read(void) noexcept
	{
		T val = m_Data[m_Read];
		m_Read = (m_Read + 1) % m_Write;
		return val;
	}
private:
	T *m_Data;
	N m_Write, m_Read, m_Size;
};
