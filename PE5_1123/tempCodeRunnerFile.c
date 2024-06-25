
// void resort(int i){
//     int minChild;
//     if(arr[1] < arr[2]){

//         minChild = 1;
//     }
//     else{
//         minChild = 2;
//     }
//     int k = 0;
//     while(arr[k] < arr[minChild] && k < i){
//         int tmp = arr[k];
//         arr[k] = arr[minChild];
//         arr[minChild] = tmp;
//         k = minChild;
//         if(arr[k*2] < arr[k*2+1]){

//             minChild = k*2;
//         }
//         else{
//             minChild = k*2+1;
//         }
//     }
// }

// void delete(int max){
//     int tmp = arr[0];
//     arr[0] = arr[max -1];
//     arr[max-1] = tmp;
//     resort(max-1);
// }
