# cub3d
my first raycasting engine

## basic mode
```shell
$ make


##bonus mode
```shell
$ make bonus
$./cub3d ./map/lol.cub
```

*  해상도  맥스 ( done )
*  맵 중간에 빵꾸나면 유효 처리 (done)
*  대각선 통과 못하게 처리
   *  현재 상황: 8면을 다 막아야 대각선으로도 빠지지 않는다.고로 최전방 모서리기준 대각선에 1이 없으면 유효하지 않은 맵 처리 해야되는데  유효한 맵 처리를 한다. 그래서 뚫리면 안되는데 뚫린다. 내 생각엔 대각선에 1없으면 에러 뱉게 하는게 더 수정하기 편할듯.
*  색 ", "  되게 처리 (done)
*  스프라이트 통과할 수 있게 처리(done)
*  숫자가 2개 이상 들어오면 에러 뱉게 처리 (done)
*  테스터 통과(돈)

