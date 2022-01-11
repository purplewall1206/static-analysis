; ModuleID = 'kernel/range.c'
source_filename = "kernel/range.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.range = type { i64, i64 }

@.str = private unnamed_addr constant [33 x i8] c"\013%s: run out of slot in ranges\0A\00", align 1
@__func__.subtract_range = private unnamed_addr constant [15 x i8] c"subtract_range\00", align 1

; Function Attrs: mustprogress nofree norecurse noredzone nosync nounwind null_pointer_is_valid sspstrong willreturn writeonly
define dso_local i32 @add_range(%struct.range* nocapture %0, i32 %1, i32 %2, i64 %3, i64 %4) local_unnamed_addr #0 !dbg !10 {
  call void @llvm.dbg.value(metadata %struct.range* %0, metadata !26, metadata !DIExpression()), !dbg !31
  call void @llvm.dbg.value(metadata i32 %1, metadata !27, metadata !DIExpression()), !dbg !31
  call void @llvm.dbg.value(metadata i32 %2, metadata !28, metadata !DIExpression()), !dbg !31
  call void @llvm.dbg.value(metadata i64 %3, metadata !29, metadata !DIExpression()), !dbg !31
  call void @llvm.dbg.value(metadata i64 %4, metadata !30, metadata !DIExpression()), !dbg !31
  %6 = icmp ult i64 %3, %4, !dbg !32
  %7 = icmp slt i32 %2, %1
  %8 = select i1 %6, i1 %7, i1 false, !dbg !34
  br i1 %8, label %9, label %14, !dbg !34

9:                                                ; preds = %5
  %10 = sext i32 %2 to i64, !dbg !35
  %11 = getelementptr %struct.range, %struct.range* %0, i64 %10, i32 0, !dbg !36
  store i64 %3, i64* %11, align 8, !dbg !37
  %12 = getelementptr %struct.range, %struct.range* %0, i64 %10, i32 1, !dbg !38
  store i64 %4, i64* %12, align 8, !dbg !39
  %13 = add nsw i32 %2, 1, !dbg !40
  call void @llvm.dbg.value(metadata i32 %13, metadata !28, metadata !DIExpression()), !dbg !31
  br label %14, !dbg !41

14:                                               ; preds = %5, %9
  %15 = phi i32 [ %13, %9 ], [ %2, %5 ], !dbg !31
  ret i32 %15, !dbg !42
}

; Function Attrs: nofree noredzone nosync nounwind null_pointer_is_valid sspstrong
define dso_local i32 @add_range_with_merge(%struct.range* nocapture %0, i32 %1, i32 %2, i64 %3, i64 %4) local_unnamed_addr #1 !dbg !43 {
  call void @llvm.dbg.value(metadata %struct.range* %0, metadata !45, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i32 %1, metadata !46, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i32 %2, metadata !47, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %3, metadata !48, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %4, metadata !49, metadata !DIExpression()), !dbg !68
  %6 = icmp ult i64 %3, %4, !dbg !69
  br i1 %6, label %7, label %64, !dbg !71

7:                                                ; preds = %5
  call void @llvm.dbg.value(metadata i32 %2, metadata !47, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %3, metadata !48, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %4, metadata !49, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i32 0, metadata !50, metadata !DIExpression()), !dbg !68
  %8 = icmp sgt i32 %2, 0, !dbg !72
  br i1 %8, label %9, label %52, !dbg !73

9:                                                ; preds = %7, %45
  %10 = phi i32 [ %49, %45 ], [ %2, %7 ]
  %11 = phi i64 [ %48, %45 ], [ %3, %7 ]
  %12 = phi i64 [ %47, %45 ], [ %4, %7 ]
  %13 = phi i32 [ %50, %45 ], [ 0, %7 ]
  call void @llvm.dbg.value(metadata i32 %10, metadata !47, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %11, metadata !48, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %12, metadata !49, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i32 %13, metadata !50, metadata !DIExpression()), !dbg !68
  %14 = sext i32 %13 to i64, !dbg !74
  %15 = getelementptr %struct.range, %struct.range* %0, i64 %14, !dbg !74
  %16 = getelementptr %struct.range, %struct.range* %0, i64 %14, i32 1, !dbg !76
  %17 = load i64, i64* %16, align 8, !dbg !76
  %18 = icmp eq i64 %17, 0, !dbg !74
  br i1 %18, label %45, label %19, !dbg !77

19:                                               ; preds = %9
  %20 = getelementptr inbounds %struct.range, %struct.range* %15, i64 0, i32 0, !dbg !78
  %21 = load i64, i64* %20, align 8, !dbg !78
  call void @llvm.dbg.value(metadata i64 %21, metadata !56, metadata !DIExpression()), !dbg !79
  call void @llvm.dbg.value(metadata i64 %11, metadata !58, metadata !DIExpression()), !dbg !79
  %22 = icmp ugt i64 %21, %11, !dbg !78
  %23 = select i1 %22, i64 %21, i64 %11, !dbg !78
  call void @llvm.dbg.value(metadata i64 %23, metadata !51, metadata !DIExpression()), !dbg !80
  call void @llvm.dbg.value(metadata i64 %17, metadata !59, metadata !DIExpression()), !dbg !81
  call void @llvm.dbg.value(metadata i64 %12, metadata !61, metadata !DIExpression()), !dbg !81
  %24 = icmp ult i64 %17, %12, !dbg !82
  %25 = select i1 %24, i64 %17, i64 %12, !dbg !82
  call void @llvm.dbg.value(metadata i64 %25, metadata !55, metadata !DIExpression()), !dbg !80
  %26 = icmp ugt i64 %23, %25, !dbg !83
  br i1 %26, label %45, label %27, !dbg !85

27:                                               ; preds = %19
  call void @llvm.dbg.value(metadata i64 %21, metadata !62, metadata !DIExpression()), !dbg !86
  call void @llvm.dbg.value(metadata i64 %11, metadata !64, metadata !DIExpression()), !dbg !86
  %28 = icmp ult i64 %21, %11, !dbg !87
  %29 = select i1 %28, i64 %21, i64 %11, !dbg !87
  call void @llvm.dbg.value(metadata i64 %29, metadata !48, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %17, metadata !65, metadata !DIExpression()), !dbg !88
  call void @llvm.dbg.value(metadata i64 %12, metadata !67, metadata !DIExpression()), !dbg !88
  %30 = icmp ugt i64 %17, %12, !dbg !89
  %31 = select i1 %30, i64 %17, i64 %12, !dbg !89
  call void @llvm.dbg.value(metadata i64 %31, metadata !49, metadata !DIExpression()), !dbg !68
  %32 = bitcast %struct.range* %15 to i8*, !dbg !90
  %33 = add nsw i32 %13, 1, !dbg !91
  %34 = sext i32 %33 to i64, !dbg !92
  %35 = getelementptr %struct.range, %struct.range* %0, i64 %34, !dbg !92
  %36 = bitcast %struct.range* %35 to i8*, !dbg !93
  %37 = sub i32 %10, %33, !dbg !94
  %38 = sext i32 %37 to i64, !dbg !95
  %39 = shl nsw i64 %38, 4, !dbg !96
  call void @llvm.memmove.p0i8.p0i8.i64(i8* align 1 %32, i8* align 1 %36, i64 %39, i1 false) #9, !dbg !97
  %40 = add nsw i32 %10, -1, !dbg !98
  %41 = sext i32 %40 to i64, !dbg !99
  %42 = getelementptr %struct.range, %struct.range* %0, i64 %41, i32 0, !dbg !100
  call void @llvm.dbg.value(metadata i32 %40, metadata !47, metadata !DIExpression()), !dbg !68
  %43 = add i32 %13, -1, !dbg !101
  call void @llvm.dbg.value(metadata i32 %43, metadata !50, metadata !DIExpression()), !dbg !68
  %44 = bitcast i64* %42 to i8*, !dbg !102
  call void @llvm.memset.p0i8.i64(i8* noundef align 8 dereferenceable(16) %44, i8 0, i64 16, i1 false), !dbg !103
  br label %45, !dbg !102

45:                                               ; preds = %19, %9, %27
  %46 = phi i32 [ %43, %27 ], [ %13, %9 ], [ %13, %19 ], !dbg !104
  %47 = phi i64 [ %31, %27 ], [ %12, %9 ], [ %12, %19 ]
  %48 = phi i64 [ %29, %27 ], [ %11, %9 ], [ %11, %19 ]
  %49 = phi i32 [ %40, %27 ], [ %10, %9 ], [ %10, %19 ]
  call void @llvm.dbg.value(metadata i32 %49, metadata !47, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %48, metadata !48, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i64 %47, metadata !49, metadata !DIExpression()), !dbg !68
  call void @llvm.dbg.value(metadata i32 %46, metadata !50, metadata !DIExpression()), !dbg !68
  %50 = add i32 %46, 1, !dbg !105
  call void @llvm.dbg.value(metadata i32 %50, metadata !50, metadata !DIExpression()), !dbg !68
  %51 = icmp slt i32 %50, %49, !dbg !72
  br i1 %51, label %9, label %52, !dbg !73, !llvm.loop !106

52:                                               ; preds = %45, %7
  %53 = phi i64 [ %4, %7 ], [ %47, %45 ]
  %54 = phi i64 [ %3, %7 ], [ %48, %45 ]
  %55 = phi i32 [ %2, %7 ], [ %49, %45 ]
  call void @llvm.dbg.value(metadata %struct.range* %0, metadata !26, metadata !DIExpression()), !dbg !108
  call void @llvm.dbg.value(metadata i32 %1, metadata !27, metadata !DIExpression()), !dbg !108
  call void @llvm.dbg.value(metadata i32 %55, metadata !28, metadata !DIExpression()), !dbg !108
  call void @llvm.dbg.value(metadata i64 %54, metadata !29, metadata !DIExpression()), !dbg !108
  call void @llvm.dbg.value(metadata i64 %53, metadata !30, metadata !DIExpression()), !dbg !108
  %56 = icmp ult i64 %54, %53, !dbg !110
  %57 = icmp slt i32 %55, %1
  %58 = select i1 %56, i1 %57, i1 false, !dbg !111
  br i1 %58, label %59, label %64, !dbg !111

59:                                               ; preds = %52
  %60 = sext i32 %55 to i64, !dbg !112
  %61 = getelementptr %struct.range, %struct.range* %0, i64 %60, i32 0, !dbg !113
  store i64 %54, i64* %61, align 8, !dbg !114
  %62 = getelementptr %struct.range, %struct.range* %0, i64 %60, i32 1, !dbg !115
  store i64 %53, i64* %62, align 8, !dbg !116
  %63 = add nsw i32 %55, 1, !dbg !117
  call void @llvm.dbg.value(metadata i32 %63, metadata !28, metadata !DIExpression()), !dbg !108
  br label %64, !dbg !118

64:                                               ; preds = %59, %52, %5
  %65 = phi i32 [ %2, %5 ], [ %63, %59 ], [ %55, %52 ], !dbg !68
  ret i32 %65, !dbg !119
}

; Function Attrs: noredzone nounwind null_pointer_is_valid sspstrong
define dso_local void @subtract_range(%struct.range* nocapture %0, i32 %1, i64 %2, i64 %3) local_unnamed_addr #2 !dbg !120 {
  call void @llvm.dbg.value(metadata %struct.range* %0, metadata !124, metadata !DIExpression()), !dbg !130
  call void @llvm.dbg.value(metadata i32 %1, metadata !125, metadata !DIExpression()), !dbg !130
  call void @llvm.dbg.value(metadata i64 %2, metadata !126, metadata !DIExpression()), !dbg !130
  call void @llvm.dbg.value(metadata i64 %3, metadata !127, metadata !DIExpression()), !dbg !130
  %5 = icmp ult i64 %2, %3, !dbg !131
  %6 = icmp sgt i32 %1, 0
  %7 = select i1 %5, i1 %6, i1 false, !dbg !133
  call void @llvm.dbg.value(metadata i32 0, metadata !129, metadata !DIExpression()), !dbg !130
  br i1 %7, label %8, label %51, !dbg !133

8:                                                ; preds = %4
  %9 = zext i32 %1 to i64, !dbg !134
  br label %10, !dbg !137

10:                                               ; preds = %8, %48
  %11 = phi i64 [ 0, %8 ], [ %49, %48 ]
  call void @llvm.dbg.value(metadata i64 %11, metadata !129, metadata !DIExpression()), !dbg !130
  %12 = getelementptr %struct.range, %struct.range* %0, i64 %11, i32 1, !dbg !138
  %13 = load i64, i64* %12, align 8, !dbg !138
  %14 = icmp eq i64 %13, 0, !dbg !141
  br i1 %14, label %48, label %15, !dbg !142

15:                                               ; preds = %10
  %16 = getelementptr %struct.range, %struct.range* %0, i64 %11, i32 0, !dbg !143
  %17 = load i64, i64* %16, align 8, !dbg !143
  %18 = icmp ult i64 %17, %2, !dbg !145
  %19 = icmp ugt i64 %13, %3
  %20 = select i1 %18, i1 true, i1 %19, !dbg !146
  br i1 %20, label %23, label %21, !dbg !146

21:                                               ; preds = %15
  %22 = bitcast i64* %16 to i8*, !dbg !147
  call void @llvm.memset.p0i8.i64(i8* noundef align 8 dereferenceable(16) %22, i8 0, i64 16, i1 false), !dbg !149
  br label %48, !dbg !147

23:                                               ; preds = %15
  br i1 %18, label %28, label %24, !dbg !150

24:                                               ; preds = %23
  %25 = icmp ult i64 %17, %3
  %26 = select i1 %19, i1 %25, i1 false, !dbg !152
  br i1 %26, label %27, label %48, !dbg !152

27:                                               ; preds = %24
  store i64 %3, i64* %16, align 8, !dbg !153
  br label %48, !dbg !155

28:                                               ; preds = %23
  %29 = icmp ule i64 %13, %3, !dbg !156
  %30 = icmp ugt i64 %13, %2
  %31 = select i1 %29, i1 %30, i1 false, !dbg !158
  br i1 %31, label %32, label %33, !dbg !158

32:                                               ; preds = %28
  store i64 %2, i64* %12, align 8, !dbg !159
  br label %48, !dbg !161

33:                                               ; preds = %28
  br i1 %19, label %34, label %48, !dbg !162

34:                                               ; preds = %33, %39
  %35 = phi i64 [ %40, %39 ], [ 0, %33 ]
  call void @llvm.dbg.value(metadata i64 %35, metadata !128, metadata !DIExpression()), !dbg !130
  %36 = getelementptr %struct.range, %struct.range* %0, i64 %35, i32 1, !dbg !163
  %37 = load i64, i64* %36, align 8, !dbg !163
  %38 = icmp eq i64 %37, 0, !dbg !170
  br i1 %38, label %42, label %39, !dbg !171

39:                                               ; preds = %34
  %40 = add nuw nsw i64 %35, 1, !dbg !172
  call void @llvm.dbg.value(metadata i64 %40, metadata !128, metadata !DIExpression()), !dbg !130
  %41 = icmp eq i64 %40, %9, !dbg !173
  br i1 %41, label %45, label %34, !dbg !174, !llvm.loop !175

42:                                               ; preds = %34
  %43 = and i64 %35, 4294967295, !dbg !177
  store i64 %13, i64* %36, align 8, !dbg !178
  %44 = getelementptr %struct.range, %struct.range* %0, i64 %43, i32 0, !dbg !181
  store i64 %3, i64* %44, align 8, !dbg !182
  br label %47, !dbg !183

45:                                               ; preds = %39
  %46 = call i32 (i8*, ...) @printk(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @__func__.subtract_range, i64 0, i64 0)) #10, !dbg !184
  br label %47

47:                                               ; preds = %45, %42
  store i64 %2, i64* %12, align 8, !dbg !186
  br label %48, !dbg !187

48:                                               ; preds = %24, %33, %10, %47, %32, %27, %21
  %49 = add nuw nsw i64 %11, 1, !dbg !188
  call void @llvm.dbg.value(metadata i64 %49, metadata !129, metadata !DIExpression()), !dbg !130
  %50 = icmp eq i64 %49, %9, !dbg !134
  br i1 %50, label %51, label %10, !dbg !137, !llvm.loop !189

51:                                               ; preds = %48, %4
  ret void, !dbg !191
}

; Function Attrs: cold noredzone null_pointer_is_valid
declare !dbg !192 dso_local i32 @printk(i8*, ...) local_unnamed_addr #3

; Function Attrs: noredzone nounwind null_pointer_is_valid sspstrong
define dso_local i32 @clean_sort_range(%struct.range* %0, i32 %1) local_unnamed_addr #2 !dbg !199 {
  call void @llvm.dbg.value(metadata %struct.range* %0, metadata !203, metadata !DIExpression()), !dbg !209
  call void @llvm.dbg.value(metadata i32 %1, metadata !204, metadata !DIExpression()), !dbg !209
  %3 = add i32 %1, -1, !dbg !210
  call void @llvm.dbg.value(metadata i32 %3, metadata !207, metadata !DIExpression()), !dbg !209
  call void @llvm.dbg.value(metadata i32 %1, metadata !208, metadata !DIExpression()), !dbg !209
  call void @llvm.dbg.value(metadata i32 0, metadata !205, metadata !DIExpression()), !dbg !209
  %4 = icmp sgt i32 %3, 0, !dbg !211
  br i1 %4, label %5, label %45, !dbg !214

5:                                                ; preds = %2, %40
  %6 = phi i64 [ %42, %40 ], [ 0, %2 ]
  %7 = phi i32 [ %41, %40 ], [ %3, %2 ]
  call void @llvm.dbg.value(metadata i32 %7, metadata !207, metadata !DIExpression()), !dbg !209
  call void @llvm.dbg.value(metadata i64 %6, metadata !205, metadata !DIExpression()), !dbg !209
  %8 = getelementptr %struct.range, %struct.range* %0, i64 %6, i32 1, !dbg !215
  %9 = load i64, i64* %8, align 8, !dbg !215
  %10 = icmp eq i64 %9, 0, !dbg !218
  br i1 %10, label %11, label %40, !dbg !219

11:                                               ; preds = %5
  call void @llvm.dbg.value(metadata i32 %7, metadata !206, metadata !DIExpression()), !dbg !209
  %12 = sext i32 %7 to i64, !dbg !220
  %13 = icmp slt i64 %6, %12, !dbg !220
  br i1 %13, label %14, label %26, !dbg !223

14:                                               ; preds = %11
  %15 = trunc i64 %6 to i32, !dbg !223
  br label %16, !dbg !223

16:                                               ; preds = %14, %21
  %17 = phi i64 [ %12, %14 ], [ %22, %21 ]
  call void @llvm.dbg.value(metadata i64 %17, metadata !206, metadata !DIExpression()), !dbg !209
  %18 = getelementptr %struct.range, %struct.range* %0, i64 %17, i32 1, !dbg !224
  %19 = load i64, i64* %18, align 8, !dbg !224
  %20 = icmp eq i64 %19, 0, !dbg !227
  br i1 %20, label %21, label %24, !dbg !228

21:                                               ; preds = %16
  %22 = add nsw i64 %17, -1, !dbg !229
  call void @llvm.dbg.value(metadata i64 %22, metadata !206, metadata !DIExpression()), !dbg !209
  %23 = icmp sgt i64 %22, %6, !dbg !220
  br i1 %23, label %16, label %26, !dbg !223, !llvm.loop !230

24:                                               ; preds = %16
  %25 = trunc i64 %17 to i32, !dbg !228
  br label %26, !dbg !232

26:                                               ; preds = %21, %24, %11
  %27 = phi i32 [ %7, %11 ], [ %25, %24 ], [ %15, %21 ], !dbg !234
  %28 = phi i32 [ %7, %11 ], [ %25, %24 ], [ %7, %21 ], !dbg !209
  call void @llvm.dbg.value(metadata i32 %28, metadata !207, metadata !DIExpression()), !dbg !209
  %29 = zext i32 %27 to i64, !dbg !232
  %30 = icmp eq i64 %6, %29, !dbg !232
  br i1 %30, label %45, label %31, !dbg !235

31:                                               ; preds = %26
  %32 = sext i32 %28 to i64, !dbg !236
  %33 = getelementptr %struct.range, %struct.range* %0, i64 %32, i32 0, !dbg !237
  %34 = load i64, i64* %33, align 8, !dbg !237
  %35 = getelementptr %struct.range, %struct.range* %0, i64 %6, i32 0, !dbg !238
  store i64 %34, i64* %35, align 8, !dbg !239
  %36 = getelementptr %struct.range, %struct.range* %0, i64 %32, i32 1, !dbg !240
  %37 = load i64, i64* %36, align 8, !dbg !240
  store i64 %37, i64* %8, align 8, !dbg !241
  %38 = add i32 %28, -1, !dbg !242
  call void @llvm.dbg.value(metadata i32 %38, metadata !207, metadata !DIExpression()), !dbg !209
  %39 = bitcast i64* %33 to i8*, !dbg !243
  call void @llvm.memset.p0i8.i64(i8* noundef align 8 dereferenceable(16) %39, i8 0, i64 16, i1 false), !dbg !244
  br label %40, !dbg !243

40:                                               ; preds = %5, %31
  %41 = phi i32 [ %7, %5 ], [ %38, %31 ], !dbg !209
  call void @llvm.dbg.value(metadata i32 %41, metadata !207, metadata !DIExpression()), !dbg !209
  %42 = add nuw nsw i64 %6, 1, !dbg !245
  call void @llvm.dbg.value(metadata i64 %42, metadata !205, metadata !DIExpression()), !dbg !209
  %43 = sext i32 %41 to i64, !dbg !211
  %44 = icmp slt i64 %42, %43, !dbg !211
  br i1 %44, label %5, label %45, !dbg !214, !llvm.loop !246

45:                                               ; preds = %40, %26, %2
  call void @llvm.dbg.value(metadata i32 0, metadata !205, metadata !DIExpression()), !dbg !209
  %46 = icmp sgt i32 %1, 0, !dbg !248
  br i1 %46, label %47, label %59, !dbg !251

47:                                               ; preds = %45
  %48 = zext i32 %1 to i64, !dbg !248
  br label %49, !dbg !251

49:                                               ; preds = %47, %54
  %50 = phi i64 [ 0, %47 ], [ %55, %54 ]
  call void @llvm.dbg.value(metadata i64 %50, metadata !205, metadata !DIExpression()), !dbg !209
  %51 = getelementptr %struct.range, %struct.range* %0, i64 %50, i32 1, !dbg !252
  %52 = load i64, i64* %51, align 8, !dbg !252
  %53 = icmp eq i64 %52, 0, !dbg !255
  br i1 %53, label %57, label %54, !dbg !256

54:                                               ; preds = %49
  %55 = add nuw nsw i64 %50, 1, !dbg !257
  call void @llvm.dbg.value(metadata i64 %55, metadata !205, metadata !DIExpression()), !dbg !209
  %56 = icmp eq i64 %55, %48, !dbg !248
  br i1 %56, label %59, label %49, !dbg !251, !llvm.loop !258

57:                                               ; preds = %49
  %58 = trunc i64 %50 to i32, !dbg !256
  br label %59, !dbg !260

59:                                               ; preds = %54, %57, %45
  %60 = phi i32 [ %1, %45 ], [ %58, %57 ], [ %1, %54 ], !dbg !209
  call void @llvm.dbg.value(metadata i32 %60, metadata !208, metadata !DIExpression()), !dbg !209
  %61 = bitcast %struct.range* %0 to i8*, !dbg !260
  %62 = sext i32 %60 to i64, !dbg !261
  call void @sort(i8* %61, i64 %62, i64 16, i32 (i8*, i8*)* nonnull @cmp_range, void (i8*, i8*, i32)* null) #11, !dbg !262
  ret i32 %60, !dbg !263
}

; Function Attrs: noredzone null_pointer_is_valid
declare !dbg !264 dso_local void @sort(i8*, i64, i64, i32 (i8*, i8*)*, void (i8*, i8*, i32)*) local_unnamed_addr #4

; Function Attrs: mustprogress nofree norecurse noredzone nosync nounwind null_pointer_is_valid readonly sspstrong willreturn
define internal i32 @cmp_range(i8* nocapture readonly %0, i8* nocapture readonly %1) #5 !dbg !278 {
  call void @llvm.dbg.value(metadata i8* %0, metadata !280, metadata !DIExpression()), !dbg !286
  call void @llvm.dbg.value(metadata i8* %1, metadata !281, metadata !DIExpression()), !dbg !286
  call void @llvm.dbg.value(metadata i8* %0, metadata !282, metadata !DIExpression()), !dbg !286
  call void @llvm.dbg.value(metadata i8* %1, metadata !285, metadata !DIExpression()), !dbg !286
  %3 = bitcast i8* %0 to i64*, !dbg !287
  %4 = load i64, i64* %3, align 8, !dbg !287
  %5 = bitcast i8* %1 to i64*, !dbg !289
  %6 = load i64, i64* %5, align 8, !dbg !289
  %7 = icmp ult i64 %4, %6, !dbg !290
  %8 = icmp ugt i64 %4, %6, !dbg !291
  %9 = zext i1 %8 to i32, !dbg !291
  %10 = select i1 %7, i32 -1, i32 %9, !dbg !291
  ret i32 %10, !dbg !292
}

; Function Attrs: noredzone nounwind null_pointer_is_valid sspstrong
define dso_local void @sort_range(%struct.range* %0, i32 %1) local_unnamed_addr #2 !dbg !293 {
  call void @llvm.dbg.value(metadata %struct.range* %0, metadata !297, metadata !DIExpression()), !dbg !299
  call void @llvm.dbg.value(metadata i32 %1, metadata !298, metadata !DIExpression()), !dbg !299
  %3 = bitcast %struct.range* %0 to i8*, !dbg !300
  %4 = sext i32 %1 to i64, !dbg !301
  call void @sort(i8* %3, i64 %4, i64 16, i32 (i8*, i8*)* nonnull @cmp_range, void (i8*, i8*, i32)* null) #11, !dbg !302
  ret void, !dbg !303
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #6

; Function Attrs: argmemonly nofree nounwind willreturn
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1 immarg) #7

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #8

attributes #0 = { mustprogress nofree norecurse noredzone nosync nounwind null_pointer_is_valid sspstrong willreturn writeonly "disable-tail-calls"="true" "fentry-call"="true" "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,-3dnow,-3dnowa,-aes,-avx,-avx2,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512er,-avx512f,-avx512ifma,-avx512pf,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxvnni,-f16c,-fma,-fma4,-gfni,-kl,-mmx,-pclmul,-sha,-sse,-sse2,-sse3,-sse4.1,-sse4.2,-sse4a,-ssse3,-vaes,-vpclmulqdq,-widekl,-x87,-xop" "tune-cpu"="generic" "warn-stack-size"="1024" }
attributes #1 = { nofree noredzone nosync nounwind null_pointer_is_valid sspstrong "disable-tail-calls"="true" "fentry-call"="true" "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,-3dnow,-3dnowa,-aes,-avx,-avx2,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512er,-avx512f,-avx512ifma,-avx512pf,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxvnni,-f16c,-fma,-fma4,-gfni,-kl,-mmx,-pclmul,-sha,-sse,-sse2,-sse3,-sse4.1,-sse4.2,-sse4a,-ssse3,-vaes,-vpclmulqdq,-widekl,-x87,-xop" "tune-cpu"="generic" "warn-stack-size"="1024" }
attributes #2 = { noredzone nounwind null_pointer_is_valid sspstrong "disable-tail-calls"="true" "fentry-call"="true" "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,-3dnow,-3dnowa,-aes,-avx,-avx2,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512er,-avx512f,-avx512ifma,-avx512pf,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxvnni,-f16c,-fma,-fma4,-gfni,-kl,-mmx,-pclmul,-sha,-sse,-sse2,-sse3,-sse4.1,-sse4.2,-sse4a,-ssse3,-vaes,-vpclmulqdq,-widekl,-x87,-xop" "tune-cpu"="generic" "warn-stack-size"="1024" }
attributes #3 = { cold noredzone null_pointer_is_valid "disable-tail-calls"="true" "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,-3dnow,-3dnowa,-aes,-avx,-avx2,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512er,-avx512f,-avx512ifma,-avx512pf,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxvnni,-f16c,-fma,-fma4,-gfni,-kl,-mmx,-pclmul,-sha,-sse,-sse2,-sse3,-sse4.1,-sse4.2,-sse4a,-ssse3,-vaes,-vpclmulqdq,-widekl,-x87,-xop" "tune-cpu"="generic" }
attributes #4 = { noredzone null_pointer_is_valid "disable-tail-calls"="true" "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,-3dnow,-3dnowa,-aes,-avx,-avx2,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512er,-avx512f,-avx512ifma,-avx512pf,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxvnni,-f16c,-fma,-fma4,-gfni,-kl,-mmx,-pclmul,-sha,-sse,-sse2,-sse3,-sse4.1,-sse4.2,-sse4a,-ssse3,-vaes,-vpclmulqdq,-widekl,-x87,-xop" "tune-cpu"="generic" }
attributes #5 = { mustprogress nofree norecurse noredzone nosync nounwind null_pointer_is_valid readonly sspstrong willreturn "disable-tail-calls"="true" "fentry-call"="true" "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,-3dnow,-3dnowa,-aes,-avx,-avx2,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512er,-avx512f,-avx512ifma,-avx512pf,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxvnni,-f16c,-fma,-fma4,-gfni,-kl,-mmx,-pclmul,-sha,-sse,-sse2,-sse3,-sse4.1,-sse4.2,-sse4a,-ssse3,-vaes,-vpclmulqdq,-widekl,-x87,-xop" "tune-cpu"="generic" "warn-stack-size"="1024" }
attributes #6 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #7 = { argmemonly nofree nounwind willreturn }
attributes #8 = { argmemonly nofree nounwind willreturn writeonly }
attributes #9 = { noredzone }
attributes #10 = { cold noredzone nounwind }
attributes #11 = { noredzone nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C89, file: !1, producer: "clang version 13.0.0 (https://github.com/llvm/llvm-project.git d7b669b3a30345cfcdb2fde2af6f48aa4b94845d)", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "kernel/range.c", directory: "/home/wangzc/Documents/linux-5.10.26-llvm")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 2}
!6 = !{i32 1, !"Code Model", i32 2}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{i32 1, !"override-stack-alignment", i32 8}
!9 = !{!"clang version 13.0.0 (https://github.com/llvm/llvm-project.git d7b669b3a30345cfcdb2fde2af6f48aa4b94845d)"}
!10 = distinct !DISubprogram(name: "add_range", scope: !1, file: !1, line: 12, type: !11, scopeLine: 13, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !25)
!11 = !DISubroutineType(types: !12)
!12 = !{!13, !14, !13, !13, !19, !19}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64)
!15 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "range", file: !16, line: 6, size: 128, elements: !17)
!16 = !DIFile(filename: "./include/linux/range.h", directory: "/home/wangzc/Documents/linux-5.10.26-llvm")
!17 = !{!18, !24}
!18 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !15, file: !16, line: 7, baseType: !19, size: 64)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "u64", file: !20, line: 23, baseType: !21)
!20 = !DIFile(filename: "./include/asm-generic/int-ll64.h", directory: "/home/wangzc/Documents/linux-5.10.26-llvm")
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "__u64", file: !22, line: 31, baseType: !23)
!22 = !DIFile(filename: "./include/uapi/asm-generic/int-ll64.h", directory: "/home/wangzc/Documents/linux-5.10.26-llvm")
!23 = !DIBasicType(name: "long long unsigned int", size: 64, encoding: DW_ATE_unsigned)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !15, file: !16, line: 8, baseType: !19, size: 64, offset: 64)
!25 = !{!26, !27, !28, !29, !30}
!26 = !DILocalVariable(name: "range", arg: 1, scope: !10, file: !1, line: 12, type: !14)
!27 = !DILocalVariable(name: "az", arg: 2, scope: !10, file: !1, line: 12, type: !13)
!28 = !DILocalVariable(name: "nr_range", arg: 3, scope: !10, file: !1, line: 12, type: !13)
!29 = !DILocalVariable(name: "start", arg: 4, scope: !10, file: !1, line: 12, type: !19)
!30 = !DILocalVariable(name: "end", arg: 5, scope: !10, file: !1, line: 12, type: !19)
!31 = !DILocation(line: 0, scope: !10)
!32 = !DILocation(line: 14, column: 12, scope: !33)
!33 = distinct !DILexicalBlock(scope: !10, file: !1, line: 14, column: 6)
!34 = !DILocation(line: 14, column: 6, scope: !10)
!35 = !DILocation(line: 21, column: 2, scope: !10)
!36 = !DILocation(line: 21, column: 18, scope: !10)
!37 = !DILocation(line: 21, column: 24, scope: !10)
!38 = !DILocation(line: 22, column: 18, scope: !10)
!39 = !DILocation(line: 22, column: 22, scope: !10)
!40 = !DILocation(line: 24, column: 10, scope: !10)
!41 = !DILocation(line: 26, column: 2, scope: !10)
!42 = !DILocation(line: 27, column: 1, scope: !10)
!43 = distinct !DISubprogram(name: "add_range_with_merge", scope: !1, file: !1, line: 29, type: !11, scopeLine: 31, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !44)
!44 = !{!45, !46, !47, !48, !49, !50, !51, !55, !56, !58, !59, !61, !62, !64, !65, !67}
!45 = !DILocalVariable(name: "range", arg: 1, scope: !43, file: !1, line: 29, type: !14)
!46 = !DILocalVariable(name: "az", arg: 2, scope: !43, file: !1, line: 29, type: !13)
!47 = !DILocalVariable(name: "nr_range", arg: 3, scope: !43, file: !1, line: 29, type: !13)
!48 = !DILocalVariable(name: "start", arg: 4, scope: !43, file: !1, line: 30, type: !19)
!49 = !DILocalVariable(name: "end", arg: 5, scope: !43, file: !1, line: 30, type: !19)
!50 = !DILocalVariable(name: "i", scope: !43, file: !1, line: 32, type: !13)
!51 = !DILocalVariable(name: "common_start", scope: !52, file: !1, line: 39, type: !19)
!52 = distinct !DILexicalBlock(scope: !53, file: !1, line: 38, column: 33)
!53 = distinct !DILexicalBlock(scope: !54, file: !1, line: 38, column: 2)
!54 = distinct !DILexicalBlock(scope: !43, file: !1, line: 38, column: 2)
!55 = !DILocalVariable(name: "common_end", scope: !52, file: !1, line: 39, type: !19)
!56 = !DILocalVariable(name: "__UNIQUE_ID___x0", scope: !57, file: !1, line: 44, type: !19)
!57 = distinct !DILexicalBlock(scope: !52, file: !1, line: 44, column: 18)
!58 = !DILocalVariable(name: "__UNIQUE_ID___y1", scope: !57, file: !1, line: 44, type: !19)
!59 = !DILocalVariable(name: "__UNIQUE_ID___x2", scope: !60, file: !1, line: 45, type: !19)
!60 = distinct !DILexicalBlock(scope: !52, file: !1, line: 45, column: 16)
!61 = !DILocalVariable(name: "__UNIQUE_ID___y3", scope: !60, file: !1, line: 45, type: !19)
!62 = !DILocalVariable(name: "__UNIQUE_ID___x4", scope: !63, file: !1, line: 50, type: !19)
!63 = distinct !DILexicalBlock(scope: !52, file: !1, line: 50, column: 11)
!64 = !DILocalVariable(name: "__UNIQUE_ID___y5", scope: !63, file: !1, line: 50, type: !19)
!65 = !DILocalVariable(name: "__UNIQUE_ID___x6", scope: !66, file: !1, line: 51, type: !19)
!66 = distinct !DILexicalBlock(scope: !52, file: !1, line: 51, column: 9)
!67 = !DILocalVariable(name: "__UNIQUE_ID___y7", scope: !66, file: !1, line: 51, type: !19)
!68 = !DILocation(line: 0, scope: !43)
!69 = !DILocation(line: 34, column: 12, scope: !70)
!70 = distinct !DILexicalBlock(scope: !43, file: !1, line: 34, column: 6)
!71 = !DILocation(line: 34, column: 6, scope: !43)
!72 = !DILocation(line: 38, column: 16, scope: !53)
!73 = !DILocation(line: 38, column: 2, scope: !54)
!74 = !DILocation(line: 41, column: 8, scope: !75)
!75 = distinct !DILexicalBlock(scope: !52, file: !1, line: 41, column: 7)
!76 = !DILocation(line: 41, column: 17, scope: !75)
!77 = !DILocation(line: 41, column: 7, scope: !52)
!78 = !DILocation(line: 44, column: 18, scope: !57)
!79 = !DILocation(line: 0, scope: !57)
!80 = !DILocation(line: 0, scope: !52)
!81 = !DILocation(line: 0, scope: !60)
!82 = !DILocation(line: 45, column: 16, scope: !60)
!83 = !DILocation(line: 46, column: 20, scope: !84)
!84 = distinct !DILexicalBlock(scope: !52, file: !1, line: 46, column: 7)
!85 = !DILocation(line: 46, column: 7, scope: !52)
!86 = !DILocation(line: 0, scope: !63)
!87 = !DILocation(line: 50, column: 11, scope: !63)
!88 = !DILocation(line: 0, scope: !66)
!89 = !DILocation(line: 51, column: 9, scope: !66)
!90 = !DILocation(line: 53, column: 11, scope: !52)
!91 = !DILocation(line: 53, column: 31, scope: !52)
!92 = !DILocation(line: 53, column: 23, scope: !52)
!93 = !DILocation(line: 53, column: 22, scope: !52)
!94 = !DILocation(line: 54, column: 14, scope: !52)
!95 = !DILocation(line: 54, column: 4, scope: !52)
!96 = !DILocation(line: 54, column: 25, scope: !52)
!97 = !DILocation(line: 53, column: 3, scope: !52)
!98 = !DILocation(line: 55, column: 18, scope: !52)
!99 = !DILocation(line: 55, column: 3, scope: !52)
!100 = !DILocation(line: 55, column: 23, scope: !52)
!101 = !DILocation(line: 58, column: 4, scope: !52)
!102 = !DILocation(line: 59, column: 2, scope: !53)
!103 = !DILocation(line: 56, column: 29, scope: !52)
!104 = !DILocation(line: 0, scope: !54)
!105 = !DILocation(line: 38, column: 29, scope: !53)
!106 = distinct !{!106, !73, !107}
!107 = !DILocation(line: 59, column: 2, scope: !54)
!108 = !DILocation(line: 0, scope: !10, inlinedAt: !109)
!109 = distinct !DILocation(line: 62, column: 9, scope: !43)
!110 = !DILocation(line: 14, column: 12, scope: !33, inlinedAt: !109)
!111 = !DILocation(line: 14, column: 6, scope: !10, inlinedAt: !109)
!112 = !DILocation(line: 21, column: 2, scope: !10, inlinedAt: !109)
!113 = !DILocation(line: 21, column: 18, scope: !10, inlinedAt: !109)
!114 = !DILocation(line: 21, column: 24, scope: !10, inlinedAt: !109)
!115 = !DILocation(line: 22, column: 18, scope: !10, inlinedAt: !109)
!116 = !DILocation(line: 22, column: 22, scope: !10, inlinedAt: !109)
!117 = !DILocation(line: 24, column: 10, scope: !10, inlinedAt: !109)
!118 = !DILocation(line: 26, column: 2, scope: !10, inlinedAt: !109)
!119 = !DILocation(line: 63, column: 1, scope: !43)
!120 = distinct !DISubprogram(name: "subtract_range", scope: !1, file: !1, line: 65, type: !121, scopeLine: 66, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !123)
!121 = !DISubroutineType(types: !122)
!122 = !{null, !14, !13, !19, !19}
!123 = !{!124, !125, !126, !127, !128, !129}
!124 = !DILocalVariable(name: "range", arg: 1, scope: !120, file: !1, line: 65, type: !14)
!125 = !DILocalVariable(name: "az", arg: 2, scope: !120, file: !1, line: 65, type: !13)
!126 = !DILocalVariable(name: "start", arg: 3, scope: !120, file: !1, line: 65, type: !19)
!127 = !DILocalVariable(name: "end", arg: 4, scope: !120, file: !1, line: 65, type: !19)
!128 = !DILocalVariable(name: "i", scope: !120, file: !1, line: 67, type: !13)
!129 = !DILocalVariable(name: "j", scope: !120, file: !1, line: 67, type: !13)
!130 = !DILocation(line: 0, scope: !120)
!131 = !DILocation(line: 69, column: 12, scope: !132)
!132 = distinct !DILexicalBlock(scope: !120, file: !1, line: 69, column: 6)
!133 = !DILocation(line: 69, column: 6, scope: !120)
!134 = !DILocation(line: 72, column: 16, scope: !135)
!135 = distinct !DILexicalBlock(scope: !136, file: !1, line: 72, column: 2)
!136 = distinct !DILexicalBlock(scope: !120, file: !1, line: 72, column: 2)
!137 = !DILocation(line: 72, column: 2, scope: !136)
!138 = !DILocation(line: 73, column: 17, scope: !139)
!139 = distinct !DILexicalBlock(scope: !140, file: !1, line: 73, column: 7)
!140 = distinct !DILexicalBlock(scope: !135, file: !1, line: 72, column: 27)
!141 = !DILocation(line: 73, column: 8, scope: !139)
!142 = !DILocation(line: 73, column: 7, scope: !140)
!143 = !DILocation(line: 76, column: 25, scope: !144)
!144 = distinct !DILexicalBlock(scope: !140, file: !1, line: 76, column: 7)
!145 = !DILocation(line: 76, column: 13, scope: !144)
!146 = !DILocation(line: 76, column: 31, scope: !144)
!147 = !DILocation(line: 79, column: 4, scope: !148)
!148 = distinct !DILexicalBlock(scope: !144, file: !1, line: 76, column: 55)
!149 = !DILocation(line: 78, column: 17, scope: !148)
!150 = !DILocation(line: 82, column: 31, scope: !151)
!151 = distinct !DILexicalBlock(scope: !140, file: !1, line: 82, column: 7)
!152 = !DILocation(line: 82, column: 53, scope: !151)
!153 = !DILocation(line: 84, column: 19, scope: !154)
!154 = distinct !DILexicalBlock(scope: !151, file: !1, line: 83, column: 29)
!155 = !DILocation(line: 85, column: 4, scope: !154)
!156 = !DILocation(line: 89, column: 37, scope: !157)
!157 = distinct !DILexicalBlock(scope: !140, file: !1, line: 89, column: 7)
!158 = !DILocation(line: 89, column: 53, scope: !157)
!159 = !DILocation(line: 91, column: 17, scope: !160)
!160 = distinct !DILexicalBlock(scope: !157, file: !1, line: 90, column: 29)
!161 = !DILocation(line: 92, column: 4, scope: !160)
!162 = !DILocation(line: 95, column: 7, scope: !140)
!163 = !DILocation(line: 98, column: 18, scope: !164)
!164 = distinct !DILexicalBlock(scope: !165, file: !1, line: 98, column: 9)
!165 = distinct !DILexicalBlock(scope: !166, file: !1, line: 97, column: 29)
!166 = distinct !DILexicalBlock(scope: !167, file: !1, line: 97, column: 4)
!167 = distinct !DILexicalBlock(scope: !168, file: !1, line: 97, column: 4)
!168 = distinct !DILexicalBlock(scope: !169, file: !1, line: 95, column: 53)
!169 = distinct !DILexicalBlock(scope: !140, file: !1, line: 95, column: 7)
!170 = !DILocation(line: 98, column: 22, scope: !164)
!171 = !DILocation(line: 98, column: 9, scope: !165)
!172 = !DILocation(line: 97, column: 25, scope: !166)
!173 = !DILocation(line: 97, column: 18, scope: !166)
!174 = !DILocation(line: 97, column: 4, scope: !167)
!175 = distinct !{!175, !174, !176}
!176 = !DILocation(line: 100, column: 4, scope: !167)
!177 = !DILocation(line: 98, column: 9, scope: !164)
!178 = !DILocation(line: 102, column: 18, scope: !179)
!179 = distinct !DILexicalBlock(scope: !180, file: !1, line: 101, column: 16)
!180 = distinct !DILexicalBlock(scope: !168, file: !1, line: 101, column: 8)
!181 = !DILocation(line: 103, column: 14, scope: !179)
!182 = !DILocation(line: 103, column: 20, scope: !179)
!183 = !DILocation(line: 104, column: 4, scope: !179)
!184 = !DILocation(line: 105, column: 5, scope: !185)
!185 = distinct !DILexicalBlock(scope: !180, file: !1, line: 104, column: 11)
!186 = !DILocation(line: 108, column: 17, scope: !168)
!187 = !DILocation(line: 109, column: 4, scope: !168)
!188 = !DILocation(line: 72, column: 23, scope: !135)
!189 = distinct !{!189, !137, !190}
!190 = !DILocation(line: 111, column: 2, scope: !136)
!191 = !DILocation(line: 112, column: 1, scope: !120)
!192 = !DISubprogram(name: "printk", scope: !193, file: !193, line: 176, type: !194, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized, retainedNodes: !2)
!193 = !DIFile(filename: "./include/linux/printk.h", directory: "/home/wangzc/Documents/linux-5.10.26-llvm")
!194 = !DISubroutineType(types: !195)
!195 = !{!13, !196, null}
!196 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !197, size: 64)
!197 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !198)
!198 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!199 = distinct !DISubprogram(name: "clean_sort_range", scope: !1, file: !1, line: 126, type: !200, scopeLine: 127, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !202)
!200 = !DISubroutineType(types: !201)
!201 = !{!13, !14, !13}
!202 = !{!203, !204, !205, !206, !207, !208}
!203 = !DILocalVariable(name: "range", arg: 1, scope: !199, file: !1, line: 126, type: !14)
!204 = !DILocalVariable(name: "az", arg: 2, scope: !199, file: !1, line: 126, type: !13)
!205 = !DILocalVariable(name: "i", scope: !199, file: !1, line: 128, type: !13)
!206 = !DILocalVariable(name: "j", scope: !199, file: !1, line: 128, type: !13)
!207 = !DILocalVariable(name: "k", scope: !199, file: !1, line: 128, type: !13)
!208 = !DILocalVariable(name: "nr_range", scope: !199, file: !1, line: 128, type: !13)
!209 = !DILocation(line: 0, scope: !199)
!210 = !DILocation(line: 128, column: 19, scope: !199)
!211 = !DILocation(line: 130, column: 16, scope: !212)
!212 = distinct !DILexicalBlock(scope: !213, file: !1, line: 130, column: 2)
!213 = distinct !DILexicalBlock(scope: !199, file: !1, line: 130, column: 2)
!214 = !DILocation(line: 130, column: 2, scope: !213)
!215 = !DILocation(line: 131, column: 16, scope: !216)
!216 = distinct !DILexicalBlock(scope: !217, file: !1, line: 131, column: 7)
!217 = distinct !DILexicalBlock(scope: !212, file: !1, line: 130, column: 26)
!218 = !DILocation(line: 131, column: 7, scope: !216)
!219 = !DILocation(line: 131, column: 7, scope: !217)
!220 = !DILocation(line: 133, column: 17, scope: !221)
!221 = distinct !DILexicalBlock(scope: !222, file: !1, line: 133, column: 3)
!222 = distinct !DILexicalBlock(scope: !217, file: !1, line: 133, column: 3)
!223 = !DILocation(line: 133, column: 3, scope: !222)
!224 = !DILocation(line: 134, column: 17, scope: !225)
!225 = distinct !DILexicalBlock(scope: !226, file: !1, line: 134, column: 8)
!226 = distinct !DILexicalBlock(scope: !221, file: !1, line: 133, column: 27)
!227 = !DILocation(line: 134, column: 8, scope: !225)
!228 = !DILocation(line: 134, column: 8, scope: !226)
!229 = !DILocation(line: 133, column: 23, scope: !221)
!230 = distinct !{!230, !223, !231}
!231 = !DILocation(line: 138, column: 3, scope: !222)
!232 = !DILocation(line: 139, column: 9, scope: !233)
!233 = distinct !DILexicalBlock(scope: !217, file: !1, line: 139, column: 7)
!234 = !DILocation(line: 0, scope: !222)
!235 = !DILocation(line: 139, column: 7, scope: !217)
!236 = !DILocation(line: 141, column: 20, scope: !217)
!237 = !DILocation(line: 141, column: 29, scope: !217)
!238 = !DILocation(line: 141, column: 12, scope: !217)
!239 = !DILocation(line: 141, column: 18, scope: !217)
!240 = !DILocation(line: 142, column: 29, scope: !217)
!241 = !DILocation(line: 142, column: 18, scope: !217)
!242 = !DILocation(line: 145, column: 4, scope: !217)
!243 = !DILocation(line: 146, column: 2, scope: !217)
!244 = !DILocation(line: 144, column: 18, scope: !217)
!245 = !DILocation(line: 130, column: 22, scope: !212)
!246 = distinct !{!246, !214, !247}
!247 = !DILocation(line: 146, column: 2, scope: !213)
!248 = !DILocation(line: 148, column: 16, scope: !249)
!249 = distinct !DILexicalBlock(scope: !250, file: !1, line: 148, column: 2)
!250 = distinct !DILexicalBlock(scope: !199, file: !1, line: 148, column: 2)
!251 = !DILocation(line: 148, column: 2, scope: !250)
!252 = !DILocation(line: 149, column: 17, scope: !253)
!253 = distinct !DILexicalBlock(scope: !254, file: !1, line: 149, column: 7)
!254 = distinct !DILexicalBlock(scope: !249, file: !1, line: 148, column: 27)
!255 = !DILocation(line: 149, column: 8, scope: !253)
!256 = !DILocation(line: 149, column: 7, scope: !254)
!257 = !DILocation(line: 148, column: 23, scope: !249)
!258 = distinct !{!258, !251, !259}
!259 = !DILocation(line: 153, column: 2, scope: !250)
!260 = !DILocation(line: 156, column: 7, scope: !199)
!261 = !DILocation(line: 156, column: 14, scope: !199)
!262 = !DILocation(line: 156, column: 2, scope: !199)
!263 = !DILocation(line: 158, column: 2, scope: !199)
!264 = !DISubprogram(name: "sort", scope: !265, file: !265, line: 12, type: !266, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized, retainedNodes: !2)
!265 = !DIFile(filename: "./include/linux/sort.h", directory: "/home/wangzc/Documents/linux-5.10.26-llvm")
!266 = !DISubroutineType(types: !267)
!267 = !{null, !268, !269, !269, !270, !275}
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!269 = !DIBasicType(name: "long unsigned int", size: 64, encoding: DW_ATE_unsigned)
!270 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !271, size: 64)
!271 = !DISubroutineType(types: !272)
!272 = !{!13, !273, !273}
!273 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !274, size: 64)
!274 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!275 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !276, size: 64)
!276 = !DISubroutineType(types: !277)
!277 = !{null, !268, !268, !13}
!278 = distinct !DISubprogram(name: "cmp_range", scope: !1, file: !1, line: 114, type: !271, scopeLine: 115, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !279)
!279 = !{!280, !281, !282, !285}
!280 = !DILocalVariable(name: "x1", arg: 1, scope: !278, file: !1, line: 114, type: !273)
!281 = !DILocalVariable(name: "x2", arg: 2, scope: !278, file: !1, line: 114, type: !273)
!282 = !DILocalVariable(name: "r1", scope: !278, file: !1, line: 116, type: !283)
!283 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !284, size: 64)
!284 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !15)
!285 = !DILocalVariable(name: "r2", scope: !278, file: !1, line: 117, type: !283)
!286 = !DILocation(line: 0, scope: !278)
!287 = !DILocation(line: 119, column: 10, scope: !288)
!288 = distinct !DILexicalBlock(scope: !278, file: !1, line: 119, column: 6)
!289 = !DILocation(line: 119, column: 22, scope: !288)
!290 = !DILocation(line: 119, column: 16, scope: !288)
!291 = !DILocation(line: 119, column: 6, scope: !278)
!292 = !DILocation(line: 124, column: 1, scope: !278)
!293 = distinct !DISubprogram(name: "sort_range", scope: !1, file: !1, line: 161, type: !294, scopeLine: 162, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !296)
!294 = !DISubroutineType(types: !295)
!295 = !{null, !14, !13}
!296 = !{!297, !298}
!297 = !DILocalVariable(name: "range", arg: 1, scope: !293, file: !1, line: 161, type: !14)
!298 = !DILocalVariable(name: "nr_range", arg: 2, scope: !293, file: !1, line: 161, type: !13)
!299 = !DILocation(line: 0, scope: !293)
!300 = !DILocation(line: 164, column: 7, scope: !293)
!301 = !DILocation(line: 164, column: 14, scope: !293)
!302 = !DILocation(line: 164, column: 2, scope: !293)
!303 = !DILocation(line: 165, column: 1, scope: !293)
