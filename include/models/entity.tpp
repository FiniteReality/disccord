namespace disccord
{
    namespace models
    {
        template <typename T>
        entity<T>::entity()
            : id(0), attached(false)
        { }
        
        template <typename T>
        entity<T> entity<T>::create(T id, bool attached)
        {
            auto result = entity<T>();

            result.id = id;
            result.attached = attached;

            return result;
        }

        template <typename T>
        entity<T>::~entity()
        { }
        
        template <typename T>
        T entity<T>::getId()
        {
            return id;
        }
    }
}