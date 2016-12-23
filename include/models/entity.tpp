namespace disccord
{
    namespace models
    {
        template <typename T>
        entity::entity(T id, bool attached)
            : id(id), attached(attached)
        { }
        
        template <typename T>
        T entity::getId()
        {
            return id;
        }
    }
}