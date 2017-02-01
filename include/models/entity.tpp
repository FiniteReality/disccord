namespace disccord
{
    namespace models
    {
        template <typename T>
        entity<T>::entity()
            : id(0), attached(false)
        { }
        
        template <typename T>
        entity<T>::entity(T id, bool attached)
            : id(id), attached(attached)
        { }
        
        template <typename T>
        T entity<T>::getId()
        {
            return id;
        }
    }
}