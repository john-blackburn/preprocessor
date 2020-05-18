#define MI(_class, _name) MI_NAME(_class, #_name, _name) 

#define MI_NAME(_class, _name, _func) PMethodInfo(new MethodInfo(_name, &_class::_func))

MI(std::atomic_bool, store)
