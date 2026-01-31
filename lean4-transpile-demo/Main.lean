def fibonacci (n : Nat) : Nat :=
  if n < 2 then n else fibonacci (n - 1) + fibonacci (n - 2)

def main : IO Unit :=
  IO.println s!"fib(10) = {fibonacci 10}"

