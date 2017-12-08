package main
import (
"fmt"
"sync"
"time"
)
func main(){
	mutex1:=&sync.Mutex{}
	mutex2:=&sync.Mutex{}
	go func(){
		mutex1.Lock()
		fmt.Println("routine1 has start and get mutex1,wait to get mutex2,loading.......")
		time.Sleep(time.Second)
		mutex2.Lock()
		fmt.Println("routine1 has start and get mutex1,already get mutex2,ending.......")
		time.Sleep(time.Second)
		mutex2.Unlock()
		mutex1.Unlock()
		time.Sleep(time.Millisecond)
	}()
	go func(){
		mutex2.Lock()
		fmt.Println("routine2 has start and get mutex2,wait to get mutex1,loading.......")
		time.Sleep(time.Second)
		mutex1.Lock()
		fmt.Println("routine2 has start and get mutex2,already get mutex1,ending.......")
		time.Sleep(time.Second)
		mutex1.Unlock()
		mutex2.Unlock()
		time.Sleep(time.Millisecond)
	}()

	time.Sleep(time.Second*20)
}

