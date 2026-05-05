#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue implementation
int queue[MAX];
int front = -1, rear = -1;

// Stack implementation
int stack[MAX];
int top = -1;

// Enqueue
void enqueue(int value) {
    if (rear == MAX - 1) return;

    if (front == -1) front = 0;
    queue[++rear] = value;
}

// Dequeue
int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

// Push
void push(int value) {
    if (top == MAX - 1) return;
    stack[++top] = value;
}

// Pop
int pop() {
    if (top == -1) return -1;
    return stack[top--];
}

// Reverse queue
void reverseQueue() {
    // Step 1: Move queue → stack
    while (front <= rear) {
        push(dequeue());
    }

    // Reset queue
    front = 0;
    rear = -1;

    // Step 2: Move stack → queue
    while (top != -1) {
        enqueue(pop());
    }
}

// Display queue
void display() {
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
}

// Main
int main() {
    int N, value;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &value);
        enqueue(value);
    }

    reverseQueue();

    display();

    return 0;
}