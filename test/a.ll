; ModuleID = 'a.c'
source_filename = "a.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.s = type { i32, i32, i8, %struct.d, %struct.d* }
%struct.d = type { i32 }

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.s, align 8
  %3 = alloca i32*, align 8
  store i32 0, i32* %1, align 4
  %4 = getelementptr inbounds %struct.s, %struct.s* %2, i32 0, i32 0
  store i32 1, i32* %4, align 8
  %5 = getelementptr inbounds %struct.s, %struct.s* %2, i32 0, i32 1
  store i32 2, i32* %5, align 4
  %6 = getelementptr inbounds %struct.s, %struct.s* %2, i32 0, i32 2
  store i8 99, i8* %6, align 8
  %7 = getelementptr inbounds %struct.s, %struct.s* %2, i32 0, i32 3
  %8 = getelementptr inbounds %struct.s, %struct.s* %2, i32 0, i32 4
  store %struct.d* %7, %struct.d** %8, align 8
  %9 = getelementptr inbounds %struct.s, %struct.s* %2, i32 0, i32 3
  %10 = getelementptr inbounds %struct.d, %struct.d* %9, i32 0, i32 0
  store i32* %10, i32** %3, align 8
  %11 = load i32*, i32** %3, align 8
  store i32 3, i32* %11, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"clang version 13.0.0 (https://github.com/llvm/llvm-project.git d7b669b3a30345cfcdb2fde2af6f48aa4b94845d)"}
