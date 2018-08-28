# MP-Algorithm

**Morris-Pratt algorithm** is a faster way to find a pattern in text. Compared with BF algorithm, it is more effecient when we find a wrong character. Rather than break the loop and restart, there is a default function in MP algorithm which can tell the shortcut back-to position. Hence, we don't need to restart when we find a incorrect character. It is more benefit when the pattern is repeated, similar elements, and so on.

You can check more detailed explanation: http://www-igm.univ-mlv.fr/~lecroq/string/node7.html 

## Instructions
I add some functions to expand its scope. We can use the expression like "(a)+" to represent that our target is "numbers of 'a'".

**Limitation**

1. The input only for the English characters (26 items). For example, "aass" is legal, while "$$%^&++--" is illegal.

2. You can use () and + to represent repeat in the pattern. For example, "s(aa)+" means that the target is to find a 's' and even numbers of 'a' (Not including 0 time).

3. It can only reads one layer. No recursion in the project. For example, "s(s(aa)+)+" is illegal.

4. Be careful when you come up with a pattern. The repeat part should be well arranged. For example, "as(as)+a" is illegal, and the right one is "(as)+a".

5. It can accept only one repeat part. For example, "s(s)+aa(s)+" is illegal.

**Perform**

<img width="482" alt="124" src="https://user-images.githubusercontent.com/41135423/44641850-c4e49400-a9fb-11e8-80be-0ce39859e94b.png">
