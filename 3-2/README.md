<GCD(최대공약수) 알고리즘: 유클리드 호제법>
두 정수 a, b에 대해 (보통 a ≥ b가 아니어도 됨)

gcd(a, b) = gcd(b, a mod b)
b가 0이 되면 그때의 a가 최대공약수

[Pseudo code]
function GCD(a, b):
a = abs(a)
b = abs(b)
while b != 0:
r = a % b
a = b
b = r
return a

<LCM(최소공배수) 알고리즘>

lcm(a, b) = abs(a _ b) / gcd(a, b)
단, 곱셈 overflow를 줄이기 위해 보통 아래처럼 계산: lcm(a, b) = abs((a / gcd(a, b)) _ b)
0이 포함되면 최소공배수는 0으로 정의: lcm(0, b) = 0, lcm(a, 0) = 0

[Pseudo code]
function LCM(a, b):
if a == 0 or b == 0:
return 0
g = GCD(a, b)
return abs((a / g) \* b)
