#include <gtest/gtest.h>

extern "C" {
#include "ft_list.h"
}

// create
TEST(ft_list_create, normal) {
	t_list *list;

	list = ft_list_create();
	ASSERT_TRUE(list != nullptr);
	ASSERT_TRUE(list->head == nullptr);
	ASSERT_TRUE(list->tail == nullptr);
	ASSERT_TRUE(list->size == 0);
}

// push_front
TEST(ft_list_push_front, normal) {
	t_list *list;
	int data = 42;

	list = ft_list_create();
	ft_list_push_front(list, &data);
	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 1);
	ASSERT_TRUE(list->head->data == &data);
	ASSERT_TRUE(list->tail->data == &data);
	ASSERT_TRUE(list->head->next == nullptr);
	ASSERT_TRUE(list->head->prev == nullptr);
	ASSERT_TRUE(list->tail->next == nullptr);
	ASSERT_TRUE(list->tail->prev == nullptr);
}

// push_back
TEST(ft_list_push_back, normal) {
	t_list *list;
	int data = 42;

	list = ft_list_create();
	ft_list_push_back(list, &data);
	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 1);
	ASSERT_TRUE(list->head->data == &data);
	ASSERT_TRUE(list->tail->data == &data);
	ASSERT_TRUE(list->head->next == nullptr);
	ASSERT_TRUE(list->head->prev == nullptr);
	ASSERT_TRUE(list->tail->next == nullptr);
	ASSERT_TRUE(list->tail->prev == nullptr);
}

// 複数push
// push_front, push_back両方
TEST(ft_list_push, normal) {
	t_list *list;
	int data[3] = {42, 43, 44};

	list = ft_list_create();
	ft_list_push_front(list, &data[0]);
	ft_list_push_back(list, &data[1]);
	ft_list_push_front(list, &data[2]);
	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 3);
	ASSERT_TRUE(list->head->data == &data[2]);
	ASSERT_TRUE(list->head->next->data == &data[0]);
	ASSERT_TRUE(list->head->next->next->data == &data[1]);
	ASSERT_TRUE(list->tail->data == &data[1]);
	ASSERT_TRUE(list->tail->prev->data == &data[0]);
	ASSERT_TRUE(list->tail->prev->prev->data == &data[2]);
}

// insert
TEST(ft_list_insert, normal) {
	t_list *list;
	int data[3] = {42, 43, 44};

	list = ft_list_create();
	ft_list_push_back(list, &data[0]);
	ft_list_push_back(list, &data[1]);
	ft_list_push_back(list, &data[2]);
	int *insert_data = new int(99);
	ft_list_insert(list, list->head->next, insert_data);

	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 4);
	ASSERT_TRUE(list->head->data == &data[0]);
	ASSERT_TRUE(list->head->next->data == insert_data);
	ASSERT_TRUE(list->head->next->next->data == &data[1]);
	ASSERT_TRUE(list->head->next->next->next->data == &data[2]);
	ASSERT_TRUE(list->tail->data == &data[2]);
	ASSERT_TRUE(list->tail->prev->data == &data[1]);
	ASSERT_TRUE(list->tail->prev->prev->data == insert_data);
	ASSERT_TRUE(list->tail->prev->prev->prev->data == &data[0]);
}

// find
TEST(ft_list_find, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	auto pred = [](void *data, void *ref) -> bool {
		return *(int *) data == *(int *) ref;
	};
	void *found = ft_list_find(list, &data[1], pred);
	ASSERT_TRUE(found == &data[1]);
}

// pop_front
TEST(ft_list_pop_front, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	for (int &i: data)
		ASSERT_TRUE(ft_list_pop_front(list) == &i);
	ASSERT_TRUE(list->head == nullptr);
	ASSERT_TRUE(list->tail == nullptr);
	ASSERT_TRUE(list->size == 0);
}

// pop_back
TEST(ft_list_pop_back, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	for (int i = 2; i >= 0; i--)
		ASSERT_TRUE(ft_list_pop_back(list) == &data[i]);
	ASSERT_TRUE(list->head == nullptr);
	ASSERT_TRUE(list->tail == nullptr);
	ASSERT_TRUE(list->size == 0);
}

// remove
TEST(ft_list_remove, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	ft_list_remove(list, list->head->next, nullptr);
	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 2);
	ASSERT_TRUE(list->head->data == &data[0]);
	ASSERT_TRUE(list->head->next->data == &data[2]);
	ASSERT_TRUE(list->tail->data == &data[2]);
	ASSERT_TRUE(list->tail->prev->data == &data[0]);
}

// remove_if
TEST(ft_list_remove_if, normal) {
	int data[5] = {1, 2, 3, 4, 5};
	t_list *list;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	ft_list_remove_if(list, nullptr, [](void *data, void *ref) -> bool {
		return *(int *) data % 2 == 0;
	}, nullptr);
	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 3);
	ASSERT_TRUE(list->head->data == &data[0]);
	ASSERT_TRUE(list->head->next->data == &data[2]);
	ASSERT_TRUE(list->head->next->next->data == &data[4]);
	ASSERT_TRUE(list->tail->data == &data[4]);
	ASSERT_TRUE(list->tail->prev->data == &data[2]);
	ASSERT_TRUE(list->tail->prev->prev->data == &data[0]);
}

// copy
TEST(ft_list_copy, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;
	t_list *copy;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	auto copy_func = [](void *data) -> void * {
		return new int(*(int *) data);
	};
	copy = ft_list_copy(list, copy_func, nullptr);
	// 元のリストは変更されない
	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 3);
	// コピーされたリストを確認
	ASSERT_TRUE(copy->head != nullptr);
	ASSERT_TRUE(copy->tail != nullptr);
	ASSERT_TRUE(copy->size == 3);
	ASSERT_TRUE(*(int *) copy->head->data == 42);
	ASSERT_TRUE(*(int *) copy->head->next->data == 43);
	ASSERT_TRUE(*(int *) copy->head->next->next->data == 44);
	ASSERT_TRUE(*(int *) copy->tail->data == 44);
	ASSERT_TRUE(*(int *) copy->tail->prev->data == 43);
	ASSERT_TRUE(*(int *) copy->tail->prev->prev->data == 42);
	// アドレスは元とは違う
	ASSERT_TRUE(copy->head->data != list->head->data);
	ASSERT_TRUE(copy->head->next->data != list->head->next->data);
	ASSERT_TRUE(copy->head->next->next->data != list->head->next->next->data);
}

// filter
TEST(ft_list_filter, normal) {
	int data[5] = {1, 2, 3, 4, 5};
	t_list *list;
	t_list *filtered;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	auto filter_func = [](void *data) -> bool {
		return *(int *) data % 2 == 0;
	};
	auto copy_func = [](void *data) -> void * {
		return new int(*(int *) data);
	};
	filtered = ft_list_filter(list, filter_func, copy_func, nullptr);
	ASSERT_TRUE(filtered->head != nullptr);
	ASSERT_TRUE(filtered->tail != nullptr);
	ASSERT_TRUE(filtered->size == 2);
	ASSERT_TRUE(*(int *) filtered->head->data == 2);
	ASSERT_TRUE(*(int *) filtered->head->next->data == 4);
	ASSERT_TRUE(*(int *) filtered->tail->data == 4);
	ASSERT_TRUE(*(int *) filtered->tail->prev->data == 2);
}

// exclude
TEST(ft_list_exclude, normal) {
	int data[5] = {1, 2, 3, 4, 5};
	t_list *list;
	t_list *excluded;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	auto exclude_func = [](void *data) -> bool {
		return *(int *) data % 2 == 0;
	};
	auto copy_func = [](void *data) -> void * {
		return new int(*(int *) data);
	};
	excluded = ft_list_exclude(list, exclude_func, copy_func, nullptr);
	ASSERT_TRUE(excluded->head != nullptr);
	ASSERT_TRUE(excluded->tail != nullptr);
	ASSERT_TRUE(excluded->size == 3);
	ASSERT_TRUE(*(int *) excluded->head->data == 1);
	ASSERT_TRUE(*(int *) excluded->head->next->data == 3);
	ASSERT_TRUE(*(int *) excluded->head->next->next->data == 5);
	ASSERT_TRUE(*(int *) excluded->tail->data == 5);
	ASSERT_TRUE(*(int *) excluded->tail->prev->data == 3);
	ASSERT_TRUE(*(int *) excluded->tail->prev->prev->data == 1);
}

// clear
TEST(ft_list_clear, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	ft_list_clear(list, nullptr);
	ASSERT_TRUE(list->head == nullptr);
	ASSERT_TRUE(list->tail == nullptr);
	ASSERT_TRUE(list->size == 0);
}

// iter
TEST(ft_list_iter, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;
	t_list *copy;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	auto copy_func = [](void *data) -> void * {
		return new int(*(int *) data);
	};
	copy = ft_list_copy(list, copy_func, nullptr);
	auto iter_func = [](void *data) -> void {
		*(int *) data += 1;
	};
	ft_list_iter(copy, iter_func);
	ASSERT_TRUE(*(int *) copy->head->data == 43);
	ASSERT_TRUE(*(int *) copy->head->next->data == 44);
	ASSERT_TRUE(*(int *) copy->head->next->next->data == 45);
	ASSERT_TRUE(*(int *) copy->tail->data == 45);
	ASSERT_TRUE(*(int *) copy->tail->prev->data == 44);
	ASSERT_TRUE(*(int *) copy->tail->prev->prev->data == 43);
}

// iter_enumerate
TEST(ft_list_iter_enumerate, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;

	list = ft_list_create();
	for (int &i: data) {
		ft_list_push_back(list, &i);
	};
	auto iter_func = [](size_t i, void *data) -> void {
		*(int *) data += (int) i * 100;
	};
	ft_list_iter_enumerate(list, iter_func);
	ASSERT_TRUE(*(int *) list->head->data == 42);
	ASSERT_TRUE(*(int *) list->head->next->data == 143);
	ASSERT_TRUE(*(int *) list->head->next->next->data == 244);
	ASSERT_TRUE(*(int *) list->tail->data == 244);
	ASSERT_TRUE(*(int *) list->tail->prev->data == 143);
	ASSERT_TRUE(*(int *) list->tail->prev->prev->data == 42);
}

// append
TEST(ft_list_append, normal) {
	int data1[3] = {42, 43, 44};
	int data2[3] = {45, 46, 47};

	t_list *list1;
	t_list *list2;

	list1 = ft_list_create();
	list2 = ft_list_create();
	for (int &i: data1)
		ft_list_push_back(list1, &i);
	for (int &i: data2)
		ft_list_push_back(list2, &i);
	ft_list_append(list1, list2);
	ASSERT_TRUE(list1->head != nullptr);
	ASSERT_TRUE(list1->tail != nullptr);
	ASSERT_TRUE(list1->size == 6);
	ASSERT_TRUE(*(int *) list1->head->data == 42);
	ASSERT_TRUE(*(int *) list1->head->next->data == 43);
	ASSERT_TRUE(*(int *) list1->head->next->next->data == 44);
	ASSERT_TRUE(*(int *) list1->head->next->next->next->data == 45);
	ASSERT_TRUE(*(int *) list1->head->next->next->next->next->data == 46);
	ASSERT_TRUE(*(int *) list1->head->next->next->next->next->next->data == 47);
	ASSERT_TRUE(*(int *) list1->tail->data == 47);
	ASSERT_TRUE(*(int *) list1->tail->prev->data == 46);
	ASSERT_TRUE(*(int *) list1->tail->prev->prev->data == 45);
	ASSERT_TRUE(*(int *) list1->tail->prev->prev->prev->data == 44);
	ASSERT_TRUE(*(int *) list1->tail->prev->prev->prev->prev->data == 43);
	ASSERT_TRUE(*(int *) list1->tail->prev->prev->prev->prev->prev->data == 42);
}

TEST(ft_list_append, normal_empty) {
	int data1[3] = {42, 43, 44};

	t_list *list1;
	t_list *list2;

	list1 = ft_list_create();
	list2 = ft_list_create();
	for (int &i: data1)
		ft_list_push_back(list1, &i);
	ft_list_append(list1, list2);
	ASSERT_TRUE(list1->head != nullptr);
	ASSERT_TRUE(list1->tail != nullptr);
	ASSERT_TRUE(list1->size == 3);
	ASSERT_TRUE(*(int *) list1->head->data == 42);
	ASSERT_TRUE(*(int *) list1->head->next->data == 43);
	ASSERT_TRUE(*(int *) list1->head->next->next->data == 44);
	ASSERT_TRUE(*(int *) list1->tail->data == 44);
	ASSERT_TRUE(*(int *) list1->tail->prev->data == 43);
	ASSERT_TRUE(*(int *) list1->tail->prev->prev->data == 42);
}

TEST(ft_list_append, empty_normal) {
	int data2[3] = {45, 46, 47};

	t_list *list1;
	t_list *list2;

	list1 = ft_list_create();
	list2 = ft_list_create();
	for (int &i: data2)
		ft_list_push_back(list2, &i);
	ft_list_append(list1, list2);
	ASSERT_TRUE(list1->head != nullptr);
	ASSERT_TRUE(list1->tail != nullptr);
	ASSERT_TRUE(list1->size == 3);
	ASSERT_TRUE(*(int *) list1->head->data == 45);
	ASSERT_TRUE(*(int *) list1->head->next->data == 46);
	ASSERT_TRUE(*(int *) list1->head->next->next->data == 47);
	ASSERT_TRUE(*(int *) list1->tail->data == 47);
	ASSERT_TRUE(*(int *) list1->tail->prev->data == 46);
	ASSERT_TRUE(*(int *) list1->tail->prev->prev->data == 45);
}

TEST(ft_list_append, empty_empty) {
	t_list *list1;
	t_list *list2;

	list1 = ft_list_create();
	list2 = ft_list_create();
	ft_list_append(list1, list2);
	ASSERT_TRUE(list1->head == nullptr);
	ASSERT_TRUE(list1->tail == nullptr);
	ASSERT_TRUE(list1->size == 0);
}
