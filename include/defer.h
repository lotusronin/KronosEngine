#ifndef DEFER
#define DEFER
#define CONCAT2(x,y) x##y
#define CONCAT(x,y) CONCAT2(x,y)
 
template<typename T>
struct DeferredCode
{
    T lambda;
    DeferredCode(T lambda):lambda(lambda){}
    ~DeferredCode(){lambda();}
    DeferredCode(const DeferredCode&);
    private:
        DeferredCode& operator =(const DeferredCode&);
};
 
class DeferredCodeGenerator
{
    public:
        template<typename T>
        DeferredCode<T> operator+(T t){ return t;}
};
 
#define defer const auto& CONCAT(deferVar__, __LINE__) = DeferredCodeGenerator() + [&]()

#endif //DEFER
