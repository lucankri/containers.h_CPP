#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_
#include <iterator>
#include <initializer_list>
#include <limits>
#include <iostream>

namespace s21 {
    /**
     * @brief Класс list - последовательный контейнер который поддерживает
     * вставку и удаления элементов.
     * @details Произвольный доступ не поддерживается в контейнере, поэтому для получения элемента
     * нужно больше времени.
     * Наша реализация в виде двусвязного списка, где каждый узел имеет указатель на след.
     * элемент и указатель на пред. элемент.
     * поле head_ указывает наслужебный узел (заглушка) это будет концом списка (end()).
     * 
     */
    template<typename T>
    class list {
        class ListNode;
        class ListIterator;
        class ListConstIterator;
        public:
            using value_type = T;
            using reference = T&;
            using const_reference = const T&;
            using size_type = std::size_t;
            using iterator = ListIterator;
            using const_iterator = ListConstIterator;

            /*--------------------constructos and operators list--------------------*/

            /**
             * @brief Конструктор создает пустой список в нем служебный узел
             * 
             */
            list() {
                this->size_ = 0;
                this->head_ = new ListNode;
            }

            /**
             * @brief Конструктор создает список инициализируя кaждый узел элементами
             * 
             * @param items - список элементов
             */
            list(std::initializer_list<value_type> const &items) : list() {
                for (auto element : items) {
                    this->push_back(element);
                }
            }

            /**
             * @brief Конструктор создает список размера n
             * с дефолдной инициализацией
             * 
             * @param n - количество узлов в списке
             */
            explicit list(size_type n) : list() {
                for (; n > 0; --n) {
                    this->push_back(value_type{});
                }
            }

            /**
             * @brief Конструктор создает список путем копирования из  other
             * 
             * @param other - копируемый список
             */
            list(const list& other) : list() {
                for (auto element : other) {
                    this->push_back(element);
                }
            }

            /**
             * @brief Конструктор создает список путем перемещения
             * из other в this
             * 
             * @param other - перемещаемый список
             */
            list(list&& other) : list() {
                *this = std::move(other);
            }

            /**
             * @brief Деструктор - уничтожает список
             * 
             */
            ~list() {
                this->clear();
                delete this->head_;
            }

            /**
             * @brief Оператор присваивания копированием
             * Копирует список из other в this
             * @details Логика копирования такова, если в this были узлы с элементами
             * то мы не делаем clear(), мы заменяем элемент на элемент из other,
             * таким образом мы не будем тратить время на удаления элементов и заного создавать узлы.
             * В принципе можно было бы использовать clear(), но мы ж хотим как можно быстрее скопировать элементы
             * 
             * @param other - копируемый список
             * @return list& - возращает скопированный список по ссылке
             */
            list& operator=(const list& other) {
                if (this != &other) {
                    // Создаем iterators для this и other
                    iterator this_it_begin = this->begin();
                    iterator this_it_end = this->end();
                    const_iterator other_it_begin = other.begin();
                    const_iterator other_it_end = other.end();
                    // Тут мы заполняем уже существующие узлы
                    while (this_it_begin != this_it_end && other_it_begin != other_it_end) {
                        *this_it_begin = *other_it_begin;
                        ++this_it_begin;
                        ++other_it_begin;
                    }
                    // Если элементы узлы остались в this, надо удалить их
                    while (this_it_begin != this_it_end) {
                        iterator temp = this_it_begin;
                        ++this_it_begin;
                        this->erase(temp);
                    }
                    // Если элементы остались в other, надо добавить их в this
                    while (other_it_begin != other_it_end) {
                        this->push_back(*other_it_begin);
                        ++other_it_begin;
                    }
                }
                return *this;
            }
            
            /**
             * @brief Оператор присваивания перемещением
             * @details Тут просто очищаем this и меняем указатели
             * 
             * @param other - перемещающий список
             * @return list& - возвращает перемещенный список по ссылке
             */
            list& operator=(list&& other) noexcept {
                if (this != &other) {
                    this->clear();
                    this->swap(other);
                }
                return *this;
            }

            /*----------------------------------------------------------------------*/

            /*----------------------------------methods list------------------------------------*/

            /**
             * @brief Получить доступ к первому элементу
             * 
             * @return reference
             */
            reference front() noexcept {
                return *this->begin();
            }

            /**
             * @brief Получить доступ к первому элементу
             * @details Для конст объекта
             * 
             * @return const_reference
             */
            const_reference front() const noexcept {
                return *this->begin();
            }

            /**
             * @brief Получить доступ к последнему элементу
             * 
             * @return reference
             */
            reference back() noexcept {
                return *(--this->end());
            }

            /**
             * @brief Получить доступ к последнему элементу
             * @details Для конст объекта
             * 
             * @return const_reference
             */
            const_reference back() const noexcept {
                return *(--this->end());
            }

            /**
             * @brief Проверяет, пуст ли контейнер
             * 
             * @return true - список пуст
             * @return false - список не пуст
             */
            bool empty() const noexcept {
                return this->size_ == 0;
            }

            /**
             * @brief Возвращает количество элементов
             * 
             * @return size_type - количество элементов в списке
             */
            size_type size() const noexcept {
                return this->size_;
            }

            /**
             * @brief Возвращает максимально возможное количество элементов
             * @details Значение size_t - это максимальное количество байт памяти.
             * Это значение мы получаем при помощи std::numeric_limits<size_t>::max();
             * Компилятор ограничивает объекты размером в половину адресного пространства.
             * Поэтому полученное число делим на 2.
             * Чтоб получить максимальное число в контейнере нужно полученное число
             * разделить на узел = число / sizeof(ListNode)
             * 
             * ВАЖНО!!!
             * По идее надо сделать еще минус sizeof(ListNode) то есть -1 узел
             * так как в контейнере у нас есть служебный узел tail_
             * Но мы не стали этого делать, так как в стандартной библиотеке этого не сделано,
             * в противном случае наша функция будет выводить на 1 меньше чем у стандарта
             * 
             * @return size_type - максимальное количество элементов
             */
            size_type max_size() const {
                return ((std::numeric_limits<size_type>::max() / 2) / sizeof(ListNode));
            }

            /**
             * @brief Добавляет элемент в голову
             * 
             * @param value
             */
            void push_front(const_reference value) {
                this->insert(this->begin(), value);
            }

            /**
             * @brief Добавляет элемент в конец
             * 
             * @param value 
             */
            void push_back(const_reference value) {
                this->insert(this->end(), value);
            }

            /**
             * @brief Удаляет первый элемент
             * 
             */
            void pop_front() noexcept {
                this->erase(this->begin());
            }

            /**
             * @brief Удаляет последний элемент
             * 
             */
            void pop_back() noexcept {
                this->erase(--this->end());
            }

            /**
             * @brief Возвращает итератор в начало
             * 
             * @return iterator 
             */
            iterator begin() noexcept {
                return iterator(this->head_->next_);
            }

            /**
             * @brief Возвращает итератор в начало
             * @details Для конст объекта
             * 
             * @return const_iterator 
             */
            const_iterator begin() const noexcept {
                return iterator(this->head_->next_);
            }

            /**
             * @brief Возвращает итератор в конец
             * 
             * @return iterator 
             */
            iterator end() noexcept {
                return iterator(this->head_);
            }

            /**
             * @brief Возвращает итератор в конец
             * @details Для конст объекта
             * 
             * @return const_iterator 
             */
            const_iterator end() const noexcept {
                return iterator(this->head_);
            }

            /**
             * @brief Вставляет элементы в конкретную позицию и
             * возвращает итератор, указывающий на новый элемент
             * @details Вставляет элемент перед позицией
             * 
             * @param pos - позиция
             * @param value - новый элемент который хотим вставить
             * @return iterator 
             */
            iterator insert(iterator pos, const_reference value) {
                ListNode* new_node = new ListNode(value, pos.currentNode_, pos.currentNode_->prev_);
                pos.currentNode_->prev_->next_ = new_node;
                pos.currentNode_->prev_ = new_node;
                this->size_++;
                return iterator(new_node);
            }

            /**
             * @brief Стирает элемент в позиции
             * @details Нельзя удалить end(),
             * поэтому будем запрещать это делать
             * 
             * @param pos - позиция
             */
            void erase(iterator pos) noexcept {
                if (pos != this->head_) {
                    pos.currentNode_->prev_->next_ = pos.currentNode_->next_;
                    pos.currentNode_->next_->prev_ = pos.currentNode_->prev_;
                    // На сякий случай зануляем указатели удаляемого элемента
                    pos.currentNode_->prev_ = nullptr;
                    pos.currentNode_->next_ = nullptr;
                    delete pos.currentNode_;
                    this->size_--;
                }
            }

            /**
             * @brief Mеняет содержимое
             * 
             * @param other 
             */
            void swap(list& other) {
                if (this != &other) {
                    std::swap(this->head_, other.head_);
                    std::swap(this->size_, other.size_);
                }
            }

            /**
             * @brief Объединяет два отсортированных списка
             * 
             * @param other 
             */
            void merge(list& other) {
                if (this != &other) {
                    iterator this_begin = this->begin();
                    iterator this_end = this->end();
                    iterator other_begin = other.begin();
                    iterator other_end = other.end();
                    while (this_begin != this_end && other_begin != other_end) {
                        if (*other_begin < *this_begin) {
                            this->insert(this_begin, *other_begin);
                            iterator temp = other_begin;
                            ++other_begin;
                            other.erase(temp);
                        } else {
                            ++this_begin;
                        }
                    }

                    this->splice(this->end(), other);
                }
            }

            /**
             * @brief Перемещает элементы из одного списка в другой, перед позицией pos.
             * @details Тут мы не копируем, мы просто перепривязываем узлы одного списка к другому.
             * 
             * @param pos - позиция
             * @param other
             */
            void splice(const_iterator pos, list& other) noexcept {
                if (!other.empty()) {
                    // Отцепляем от константы
                    iterator it_pos = const_cast<ListNode*>(pos.currentNode_);
                    iterator it_other_end = other.end();
                    // Меняем указатели у other
                    it_other_end.currentNode_->next_->prev_ = it_pos.currentNode_->prev_;
                    it_other_end.currentNode_->prev_->next_ = it_pos.currentNode_;

                    // Меняем указатели у this
                    it_pos.currentNode_->prev_->next_ = it_other_end.currentNode_->next_;
                    it_pos.currentNode_->prev_ = it_other_end.currentNode_->prev_;
                    // Прибовляем количество узлов в this
                    this->size_ += other.size_;
                    other.size_ = 0;

                    // список other нужно привести к состоянию пустого списка
                    // Когда служебный узел (head_) - его prev_ и next_ должны указывать на head_
                    other.head_->next_ = other.head_;
                    other.head_->prev_ = other.head_;
                }
            }

            /**
             * @brief Меняет порядок элементов в списке
             * @details Меняем только указатели, ничего не копируем т. к. это будет долго
             * 
             */
            void reverse() {
                iterator it_begin = this->begin();
                iterator it_end = this->end();
                while (it_begin != it_end) {
                    // Тут все очень просто
                    // Просто меняем указатели в узлах - next_ теперь prev_ и наоборот
                    // Так как мы поменяли местами узлы мы делаем --begin
                    std::swap(it_begin.currentNode_->next_, it_begin.currentNode_->prev_);
                    --it_begin;
                }
                // Наш злужебный узел head_ в нем тоже меняем местами указатели
                std::swap(this->head_->next_, this->head_->prev_);
            }

            /**
             * @brief Удаляет последовательные повторяющиеся элементы
             * Пример: 1, 1, 2, 1, 2 = 1, 2, 1, 2
             * 
             */
            void unique() {
                iterator it_begin = this->begin();
                iterator it_end = this->end();
                iterator it_prev = it_begin;
                ++it_begin;
                while(it_begin != it_end) {
                    if (*it_begin == *it_prev) {
                        this->erase(it_begin);
                        it_begin = it_prev;
                    } else {
                        ++it_prev;
                    }
                    ++it_begin;
                }
            }

            /**
             * @brief Сортирует элементы в порядке возрастания
             * @details Алгоритм основан на быстрой сортировке, избавился от рекурсии,
             * сделал с помощью цикла
             * 
             */
            void sort() {
                if (this->size_ > 1) {
                    //Инициализируем переменные для работы с сортировкой
                    //i_it и j_it - итераторы
                    //i и j - индексы итераторов, показывают на каком индексе стоит итератор
                    //pivot - опорный элемент
                    //lift и right - индексы границ левого и правого
                    iterator i_it, j_it, pivot_it;
                    int i, j;
                    int left = 0;
                    int right = this->size_ - 1;
                    value_type pivot;
                    list<int> lt = {left, right};
                    // В цикле до тех пор, пока наш список индексов (lt) не пуст
                    while (!lt.empty()) {
                        // Вытаскиваем из списка индексы
                        right = *(--(lt.end()));
                        lt.pop_back();
                        left = *(--(lt.end()));
                        lt.pop_back();
                        i = left;
                        j = right;
                        i_it = this->begin();
                        j_it = this->begin();
                        pivot_it = this->begin();
                        // Настраиваем наши итераторы на нужные границы и находим опорный элемент 
                        for (int i_left = 0; i_left < i; ++i_left, ++i_it);
                        for (int j_right = 0; j_right < j; ++j_right, ++j_it);
                        // Опорный элемент у нас центральный
                        for (int search_pivot = 0; search_pivot < (i + j) / 2; ++search_pivot, ++pivot_it);
                        pivot = *pivot_it;
                        while (i <= j) {
                            // левая сторона - проходимся по элементам слева на право
                            // и ищем элемент который БОЛЬШЕ опорного элемента
                            while (*i_it < pivot) { ++i; ++i_it; }
                            // Правая сторона - проходимся по элементам справа на лево
                            // и ищем элемент который МЕНЬШЕ опорного элемента
                            while (*j_it > pivot) { --j; --j_it; }
                            // пока i находится левее отностельно j
                            // мы будем менять местами элементы
                            if (i <= j) {
                                // найденные элементы  меняем местами и двигаем
                                // итераторы и идексы т.к. индексы завязаны с итераторами
                                std::swap(*i_it, *j_it);
                                ++i;
                                ++i_it;
                                --j;
                                --j_it;
                            }
                        }

                        // Проверяем если левая граница левее j
                        // тогда заносим индексы левой граница и j
                        if (left < j) {
                            lt.push_back(left);
                            lt.push_back(j);
                        }

                        // Проверяем если правая граница правее i
                        // тогда заносим индексы i и правой граница
                        if (right > i) {
                            lt.push_back(i);
                            lt.push_back(right);
                        }

                        // Таким образом мы разбили список, теперь вернемся к тем е действиям
                        // и будем сортировать наши куски на которые разбили до тех пор,
                        // пока список индексов не пустой
                    }
                }
            }

            /**
             * @brief Очищает содержимое контейнера
             * 
             */
            void clear() {
                while(this->size_ > 0) {
                    this->pop_back();
                }
            }

            /**
             * @brief Вставляет новые элементы в контейнер непосредственно перед pos
             * @details Не стал делать через insert, что бы избежать лишнего копирования
             * 
             * @tparam Args 
             * @param pos 
             * @param args 
             * @return iterator 
             */
            template<typename... Args>
            iterator emplace(const_iterator pos, Args&&... args) {
                iterator it_pos(const_cast<ListNode *>(pos.currentNode_));
                ListNode* new_node;
                for (auto element : {std::forward<Args>(args)...}) {
                    new_node = new ListNode(std::move(element), it_pos.currentNode_, it_pos.currentNode_->prev_);
                    it_pos.currentNode_->prev_->next_ = new_node;
                    it_pos.currentNode_->prev_ = new_node;
                    this->size_++;
                }
                return iterator(new_node);
            }

            /**
             * @brief Добавляет новые элементы в конец контейнера
             * @details Схожий с emplace, только добавляет в конец
             * 
             * @param args 
             */
            template<typename... Args>
            void emplace_back(Args&&... args) {
                this->emplace(this->end(), std::forward<Args>(args)...);
            }

            /**
             * @brief Добавляет новые элементы в верхнюю часть контейнера
             * @details Схожий с emplace, только добавляет в начало
             * 
             * @param args 
             */
            template<typename... Args>
            void emplace_front(Args&&... args) {
                this->emplace(this->begin(), std::forward<Args>(args)...);
            }


        private:
            /*--------------------class ListNode--------------------*/

            /**
             * @brief Класс узла в контейнере, реализующий двусвязный список
             * 
             */
            class ListNode {
                public:
                    //Конструктор для создания служебного узла (head_)
                    ListNode() {
                        this->data_ = value_type{};
                        this->next_ = this;
                        this->prev_ = this;
                    }

                    // Конструктор создания узла со значением
                    ListNode(const_reference data_, ListNode* next_, ListNode* prev_) {
                        this->data_ = data_;
                        this->next_ = next_;
                        this->prev_ = prev_;
                    }

                    ListNode(value_type&& data_, ListNode* next_, ListNode* prev_) {
                        this->data_ = std::move(data_);
                        this->next_ = next_;
                        this->prev_ = prev_;
                    }
                    
                    // Указатель на след. элемент
                    ListNode* next_;
                    // Указатель на пред. элемент
                    ListNode* prev_;
                    // Значение узла
                    value_type data_;
            };

            /*------------------------------------------------------*/

            /*--------------------class iterator--------------------*/

            /**
             * @brief Класс итератор для list, он переопределен как iterator
             * @details от класса итератора требуются некоторые действия
             */
            class ListIterator {
                friend list;
                public:
                    /**
                     * @brief Констурктор для копирования итератора
                     * 
                     * @param other
                     */
                    ListIterator(const iterator& other) {
                        this->currentNode_ = other.currentNode_;
                    }

                    /**
                     * @brief Оператор получение значение узла, на который указывает итератор
                     * 
                     * @return reference 
                     */
                    reference operator*() const noexcept {
                        return this->currentNode_->data_;
                    }

                    /**
                     * @brief Оператор префиксный инкримент - перемещение
                     * итератора вперед для обращения к следующему элементу
                     * 
                     * @return iterator& новый элемент (ссылка)
                     */
                    iterator& operator++() noexcept {
                        this->currentNode_ = this->currentNode_->next_;
                        return *this;
                    }

                    /**
                     * @brief Оператор постфиксный инкримент - перемещение
                     * итератора вперед для обращения к следующему эелменту
                     * 
                     * @return iterator значение до перемещения
                     */
                    iterator operator++(int) noexcept {
                        iterator temp = *this;
                        ++(*this);
                        return temp;
                    }

                    /**
                     * @brief Оператор префиксный декримент - перемещение
                     * итератора назад для обращения к предыдущему элементу
                     * 
                     * @return iterator& новый элемент (ссылка)
                     */
                    iterator& operator--() noexcept {
                        this->currentNode_ = this->currentNode_->prev_;
                        return *this;
                    }

                    /**
                     * @brief Оператор постфиксный декримент - перемещение
                     * итератора назад для обращения к предыдущему элементу
                     * 
                     * @return iterator значение до перемещения
                     */
                    iterator operator--(int) noexcept {
                        iterator temp = *this;
                        --(*this);
                        return temp;
                    }

                    /**
                     * @brief Два итератора равны
                     * 
                     * @param other
                     * @return true - если два итератора равны 
                     * @return false - если два итератора не равны
                     */
                    bool operator==(const iterator& other) const noexcept {
                        return this->currentNode_ == other.currentNode_;
                    }

                    /**
                     * @brief Два итератора не равны
                     * 
                     * @param other 
                     * @return true - если два итератора не равны
                     * @return false - если два итератора равны
                     */
                    bool operator!=(const iterator& other) const noexcept {
                        return this->currentNode_ != other.currentNode_;
                    }

                    /**
                     * @brief Оператор присваивания коппированием
                     * 
                     * @param other 
                     * @return iterator& 
                     */
                    iterator& operator=(const iterator& other) {
                        if (this == &other) { return *this; }

                        this->currentNode_ = other.currentNode_;
                        return *this;
                    }

                private:

                    /**
                     * @brief Конструктор поумолчанию пользователю не нужен
                     * но в реализации контейнера он нам понадобится
                     * 
                     */
                    ListIterator() {
                        this->currentNode_ = nullptr;
                    }

                    /**
                     * @brief Конструктор для инициализации итератора
                     * с парметром узла
                     * Пользователю он не нужен
                     * 
                     * @param node 
                     */
                    ListIterator(ListNode* node) {
                        this->currentNode_ = node;
                    }

                    ListNode* currentNode_;
            }; // ListIterator
            /*-------------------------------------------------------------------*/

            /*--------------------class const_iterator--------------------*/

            /**
             * @brief Класс константного итератора для list, он переопределен как const_iterator
             * @details Класс идентичен с итератором выше, но есть отличия
             * значения в итераторе нельзя будет поменять так как поле currentNode_ теперь консантное
             * и операторы == и != перегружены как дружественные, чтоб можно было сравнивать
             * const_iterator (== || !=) iterator и наоборот
             * 
             */
            class ListConstIterator {
                friend list;
                // Как дружественные
                friend bool operator==(const const_iterator& it1, const const_iterator& it2) {
                    return it1.currentNode_ == it2.currentNode_;
                }
                friend bool operator!=(const const_iterator& it1, const const_iterator& it2) {
                    return !(it1 == it2);
                }

                public:
                    ListConstIterator() = delete;
                    ListConstIterator(const iterator& other) {
                        this->currentNode_ = other.currentNode_;
                    }

                    const_reference operator*() const noexcept {
                        return this->currentNode_->data_;
                    }
                    const_iterator& operator++() noexcept {
                        if (this->currentNode_->next_ != nullptr) {
                            this->currentNode_ = this->currentNode_->next_;
                        }
                        return *this;
                    }
                    const_iterator operator++(int) noexcept {
                        const_iterator temp = *this;
                        ++(*this);
                        return temp;
                    }
                    const_iterator& operator--() noexcept {
                        if (this->currentNode_->prev_ != nullptr) {
                            this->currentNode_ = this->currentNode_->prev_;
                        }
                        return *this;
                    }
                    const_iterator operator--(int) noexcept {
                        const_iterator temp = *this;
                        --(*this);
                        return temp;
                    }
                private:
                    const ListNode* currentNode_;
            }; // ListConstIterator

            /*------------------------------------------------------*/

            // Количество элементов в контейнере
            size_type size_;
            // Указатель на служебный узел контейнера
            ListNode* head_;
    }; // list

} //s21

#endif // SRC_S21_LIST_H_
