
``` log
[61569.539180] Jonathan DEBUG: Kernel Module Inserted Successfully...
[61569.539195] This is a double linked list, where
[61569.539216] carlist and redcar point to each other
[61569.539228] Carlist next and prev now point to &redcar.list
[61569.539241]     &redcar->list: 000000004531128d
[61569.539253]      carlist.next: 000000004531128d
[61569.539266]      carlist.prev: 000000004531128d
[61569.539278] And redcar.list next and prev point to &carlist
[61569.539290]          &carlist: 00000000030ee800
[61569.539302] redcar->list.next: 00000000030ee800
[61569.539315] redcar->list.prev: 00000000030ee800
[61569.539327] carlist -> redcar
[61569.539339] What if we add bluecar to carlist?
[61569.539351]     &bluecar->list: 0000000034953136
[61569.539364]       carlist.next: 0000000034953136
[61569.539376] bluecar->list.next: 000000004531128d
[61569.539389]  redcar->list.next: 00000000030ee800
[61569.539410] carlist -> bluecar -> redcar
[61599.472940] Jonathan DEBUG: Kernel Module Removed Successfully...

```