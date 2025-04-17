#include "list_lock.h"

#include <stdio.h>
#include <stdlib.h>

//初始化链表和锁
void listInit(list_lock_t* list) {
    pthread_mutex_init(&list->mutex, NULL);
    pthread_cond_init(&list->cond, NULL);
    
    list->head = NULL;
}

//往链表尾部添加一个元素，模拟“生产者”放入数据
//添加数据到链表
void producer(list_lock_t* list, DataType value) {

    pthread_mutex_lock(&list->mutex);

    LNode* b = (LNode*)malloc(sizeof(LNode));
    if (b == NULL) {
      pthread_mutex_unlock(&list->mutex); 
      return;
    }
    b->next = NULL;
    b->value = value;
    
    if(list->head == NULL)
    {
      list->head = b;

    }
    else
    {
        LNode* a = list->head;
  
        while(a->next != NULL)
        {
          a = a->next;
        }
  
        a->next = b;
    }

    pthread_cond_signal(&list->cond);
    pthread_mutex_unlock(&list->mutex);
}

//从链表头部取出一个元素，模拟“消费者”获取数据
//消费链表中的数据
void consumer(list_lock_t* list) {
    pthread_mutex_lock(&list->mutex);

    while(list->head == NULL)
    {
        pthread_cond_wait(&list->cond, &list->mutex);
    }
    LNode* b = list->head;
    list->head = b->next;

    free(b);
    
    pthread_mutex_unlock(&list->mutex);
}

//返回链表中元素的个数
//获取链表大小
int getListSize(list_lock_t* list) {
    pthread_mutex_lock(&list->mutex);
    int n = 0;
    if(list->head == NULL)
    {
      pthread_mutex_unlock(&list->mutex);
      return 0;
    }
    else
    {
      LNode* a = list->head;
      n = 1;
      while(a->next != NULL)
      {
        a = a->next;
        n++;
      }
      pthread_mutex_unlock(&list->mutex);
      return n;
    }
}
