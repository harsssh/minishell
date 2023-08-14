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
	ft_list_insert(list, 0, &data[0]);
	ft_list_insert(list, 1, &data[1]);
	ft_list_insert(list, 1, &data[2]);
	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 3);
	ASSERT_TRUE(list->head->data == &data[0]);
	ASSERT_TRUE(list->head->next->data == &data[2]);
	ASSERT_TRUE(list->head->next->next->data == &data[1]);
	ASSERT_TRUE(list->tail->data == &data[1]);
	ASSERT_TRUE(list->tail->prev->data == &data[2]);
	ASSERT_TRUE(list->tail->prev->prev->data == &data[0]);
}

// get
TEST(ft_list_get, normal) {
	int data[3] = {42, 43, 44};
	t_list *list;

	list = ft_list_create();
	for (int &i: data)
		ft_list_push_back(list, &i);
	for (int i = 0; i < 3; i++)
		ASSERT_TRUE(ft_list_get(list, i) == &data[i]);
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
	ft_list_remove(list, 1, nullptr);
	ASSERT_TRUE(list->head != nullptr);
	ASSERT_TRUE(list->tail != nullptr);
	ASSERT_TRUE(list->size == 2);
	ASSERT_TRUE(list->head->data == &data[0]);
	ASSERT_TRUE(list->head->next->data == &data[2]);
	ASSERT_TRUE(list->tail->data == &data[2]);
	ASSERT_TRUE(list->tail->prev->data == &data[0]);
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