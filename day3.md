### 1. 删除重复对应节点

核心：构建虚拟的头节点 最后注意返回的是头节点的next 保证虚拟的头节点被删除

使用while循环不断遍历节点，如果下一个节点的值是对应的节点，进行跳过操作处理

```python

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
        head_node = ListNode(val = 0, next = head)

        current_node = head_node
  
        while current_node.next:
            if current_node.next.val == val:
                current_node.next = current_node.next.next

            else:
                current_node = current_node.next
        return head_node.next

```


### 2.  链表的设计

核心：使用虚拟的头节点来完成更删改查，注意在delete时候size的变化，从而来实现lianbiao的设计

```python

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
  
class MyLinkedList:
    def __init__(self):
        self.dummy_head = ListNode()
        self.size = 0

    def get(self, index: int) -> int:
        if index < 0 or index >= self.size:
            return -1
  
        current = self.dummy_head.next
        for i in range(index):
            current = current.next
  
        return current.val

    def addAtHead(self, val: int) -> None:
        self.dummy_head.next = ListNode(val, self.dummy_head.next)
        self.size += 1

    def addAtTail(self, val: int) -> None:
        current = self.dummy_head
        while current.next:
            current = current.next
        current.next = ListNode(val)
        self.size += 1

    def addAtIndex(self, index: int, val: int) -> None:
        if index < 0 or index > self.size:
            return
  
        current = self.dummy_head
        for i in range(index):
            current = current.next
        current.next = ListNode(val, current.next)
        self.size += 1

    def deleteAtIndex(self, index: int) -> None:
        if index < 0 or index >= self.size:
            return
  
        current = self.dummy_head
        for i in range(index):
            current = current.next
        current.next = current.next.next
        self.size -= 1

```


### 反转链表

核心：通过快慢指针进行链表的反转

```python
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:

        cur = head
        pre = None
        while cur:
            tmp = cur.next
            cur.next = pre
            pre =cur
            cur =tmp
        return pre
```
