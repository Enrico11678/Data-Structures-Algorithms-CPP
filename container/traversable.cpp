
namespace lasd {

/* ************************************************************************** */

// TraversableContainer

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const {
    Traverse([fun, &acc](const Data & value){
        acc = fun(value, acc);
    });
    return acc;
}

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data & value) const noexcept {
    bool find = false;
    Traverse([value, &find](const Data & data){
        find |= (data == value);
    });
    return find;
}

/* ************************************************************************** */

// PreOrderTraversableContainer

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
    PreOrderTraverse([fun, &acc](const Data & value){
        acc = fun(value, acc);
    });
    return acc;
}

template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

/* ************************************************************************** */

// PostOrderTraversableContainer

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const {
    PostOrderTraverse([fun, &acc](const Data & value){
        acc = fun(value, acc);
    });
    return acc;
}

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    PostOrderTraverse(fun);
}

}
