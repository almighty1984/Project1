#pragma once

template<typename T>
class Singleton {
public:
	static T& get();
			  
	static T* getPtr();

	static void setPtr(T* instance);

	static void deleteSingleton();

private:
	static T* m_instance;
};

template<typename T>
T* Singleton<T>::m_instance = 0;

template<typename T>
T* Singleton<T>::getPtr() {
	if (m_instance == nullptr) {
		m_instance = new T;
	}
	return m_instance;
}

template<typename T>
T& Singleton<T>::get() {
	if (m_instance == nullptr) {
		m_instance = new T;
	}
	return *m_instance;
}

template<typename T>
void Singleton<T>::setPtr(T* instance) {
	m_instance = instance;
}

template<typename T>
void Singleton<T>::deleteSingleton() {
	delete m_instance;
	m_instance = nullptr;
}

