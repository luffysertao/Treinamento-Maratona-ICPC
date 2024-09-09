while True:
    first = [int(i) for i in input().split()]
    N = first[0]
    A = first[1]
    
    if N == 0 and A == 0:
        break
    
    second = [int(j) for j in input().split()]
    
    soma_total = sum(second)
    
    if soma_total == A:
        print(":D")
        continue
    elif soma_total < A:
        print("-.-")
        continue
    
    second.sort(reverse=True)
    
    low, high = 0, max(second)
    
    while high - low > 1e-5: 
        mid = (low + high) / 2
        
        area_cortada = 0

        for comprimento in second:
            if comprimento > mid:
                area_cortada += comprimento - mid

        if area_cortada < A:
            high = mid
        else:
            low = mid
    
    print(f"{(low + high) / 2:.4f}")

