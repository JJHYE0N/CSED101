/*
 * 작성일: 2021.06.01
 * 학 번: 20210815
 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STRING 20

// 큐 노드 구조체 NODE 선언
//-------- 지우고 채우기 ------------//
typedef struct node
{
    char data;
    struct node* next;
} NODE;

// 큐 헤드 구조체 QUEUE 선언
typedef struct
{
    int count;
    NODE* front;
    NODE* rear;
} QUEUE;

void printQueue(QUEUE* q);
int enqueue(QUEUE* q, char data);
int dequeue(QUEUE* q, char* data);
int isEmpty(QUEUE* q);

int main()
{
    int len, i, ioRes;
    char str[MAX_STRING];
    QUEUE queue; // 큐

    // 큐 초기화
    queue.count = 0;
    queue.front = NULL;
    queue.rear = NULL;

    while (1)
    {
        printf(">> ");
        ioRes = scanf("%s", str);

        if (ioRes == EOF)
            break;

        len = strlen(str);
        for (i = 0; i < len; i++)
        {
            enqueue(&queue, str[i]); //enqueue 함수 호출
        }

        printQueue(&queue);

    } // while

    printf("bye!\n");

    return 0;
} // main

void printQueue(QUEUE* q)
{
    char data;

    printf("   ");
    while (dequeue(q, &data))
    {
        printf("%c", data);
    }
    printf("\n\n");
} // printQueue

// enqueue 
int enqueue(QUEUE* q, char data)
{
    NODE* temp;
    // 큐 노드 생성
    temp = (NODE*)malloc(sizeof(NODE));
    if (!temp) // 동적 할당 실패시
        return 0;

    // 생성한 노드에 값 설정
    temp->data = data;
    temp->next = NULL;

    if (isEmpty(q)) // 큐가 비어 있는 경우(isEmpty 함수 호출)
    {
        q->front = temp;//1
        temp->data = data;
    }
    else
    {
        q->rear->next = temp;
        temp->data = data;
    }
    q->rear = temp;
    q->count++;

    return 1;
} // enqueue

// dequeue
int dequeue(QUEUE* q, char* data)
{
    NODE* temp;
    if (isEmpty(q)) // 큐가 비어 있는 경우
        return 0;

    temp = q->front;
    *data = q->front->data;
    if (q->rear == q->front)
    {
        q->front = NULL;
        q->rear = NULL;
    }
    else
    {
        q->front = temp->next;
        free(temp);
        q->count--;
    }//temp->data.rear
    return 1;
} // dequeue

// 큐가 비어 있으면 1, 그렇지 않으면 0을 반환
int isEmpty(QUEUE* q)
{
    return q->rear == NULL;
}