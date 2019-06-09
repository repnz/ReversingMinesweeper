#pragma once
#include <Windows.h>

BOOL InitializeBitmapsAndBlockArray();
__inline BOOL IsInBoardRange(BoardPoint point);
void ChangeBlockState(BoardPoint point, BYTE blockState);
void InitializeBlockArrayBorders();
int CountNearBombs(BoardPoint point);
void RevealAllBombs(BYTE revealedBombsState);
void TickSeconds();
void ShowBlockValue(BoardPoint point);
void ExpandEmptyBlock(BoardPoint point);
DWORD GetFlagBlocksCount(BoardPoint point);
void UpdateBlockStateToClicked(BoardPoint point);
void UpdateBlockStateToUnclicked(BoardPoint point);
__inline VOID UpdateClickedBlocksState3x3(BoardPoint newClick, BoardPoint oldClick);
__inline VOID UpdateClickedBlocksStateNormal(BoardPoint point, BoardPoint oldClick);
__inline void ReleaseBlocksClick();
void UpdateClickedBlocksState(BoardPoint point);
void NotifyMinimize();
void NotifyWindowRestore();
void AddAndDisplayLeftFlags(DWORD leftFlagsToAdd);
void FinishGame(BOOL isWon);
void HandleNormalBlockClick(BoardPoint point);
void Handle3x3BlockClick(BoardPoint point);
void InitializeNewGame();
void HandleRightClick(BoardPoint point);
void HandleBlockClick();
