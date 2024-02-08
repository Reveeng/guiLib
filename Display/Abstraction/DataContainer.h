#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <utility>
#include <memory>

namespace Display
{
    namespace Abstraction
    {
        class DataContainer {

        public:
            DataContainer(char *data, bool deleteOnDestr = true):
                m_cdata(nullptr)
            {
                if (deleteOnDestr)
                    m_data = std::shared_ptr<char>(data);
                else
                    m_cdata = data;
            }
            DataContainer(const char *data):
                m_data(nullptr),
                m_cdata(data)
            {

            }
            DataContainer(DataContainer &o):
                m_data(o.m_data),
                m_cdata(o.m_cdata)
            {

            }
            DataContainer(DataContainer &&o):
                m_data(std::move(o.m_data)),
                m_cdata(std::move(o.m_cdata))
            {
                o.m_data = nullptr;
                o.m_cdata = nullptr;
            }
            ~DataContainer()
            {

            }

            const char *data() const
            {
                if (m_data)
                    return m_data.get();
                if (m_cdata)
                    return m_cdata;
                return nullptr;
            }
        private:
            std::shared_ptr<char> m_data;
            const char *m_cdata;
        };
    }
}

#endif // DATACONTAINER_H
