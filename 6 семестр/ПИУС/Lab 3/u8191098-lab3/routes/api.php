<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\ApiV1\Controllers\ExerciseController;
use App\Http\ApiV1\Controllers\ExerciseTypeController;
use App\Http\ApiV1\Controllers\MuscleGroupController;
use App\Http\ApiV1\Controllers\SetController;
use App\Http\ApiV1\Controllers\WorkoutController;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

Route::get(
    'v1/exercise-types/{exerciseTypeId}',
    [ExerciseTypeController::class, 'getById']
);

Route::get(
    'v1/exercise-types',
    [ExerciseTypeController::class, 'getAll']
);

Route::post(
    'v1/exercise-types/',
    [ExerciseTypeController::class, 'create']
);

Route::put(
    'v1/exercise-types/{exerciseTypeId}',
    [ExerciseTypeController::class, 'put']
);

Route::delete(
    'v1/exercise-types/{exerciseTypeId}',
    [ExerciseTypeController::class, 'delete']
);

Route::get(
    'v1/muscle-groups/{muscleGroupId}',
    [MuscleGroupController::class, 'getById']
);

Route::get(
    'v1/muscle-groups',
    [MuscleGroupController::class, 'getAll']
);

Route::post(
    'v1/muscle-groups/',
    [MuscleGroupController::class, 'create']
);
Route::put(
    'v1/muscle-groups/{muscleGroupId}',
    [MuscleGroupController::class, 'put']
);

Route::delete(
    'v1/muscle-groups/{muscleGroupId}',
    [MuscleGroupController::class, 'delete']
);

Route::get(
    'v1/exercises/{exerciseId}',
    [ExerciseController::class, 'getById']
);

Route::get(
    'v1/exercises',
    [ExerciseController::class, 'getAll']
);

Route::post(
    'v1/exercises/',
    [ExerciseController::class, 'create']
);
Route::put(
    'v1/exercises/{exerciseId}',
    [ExerciseController::class, 'put']
);

Route::patch(
    'v1/exercises/{exerciseId}',
    [ExerciseController::class, 'patch']
);

Route::delete(
    'v1/exercises/{exerciseId}',
    [ExerciseController::class, 'delete']
);

Route::get(
    'v1/sets/{setId}',
    [SetController::class, 'getById']
);

Route::get(
    'v1/sets',
    [SetController::class, 'getAll']
);

Route::post(
    'v1/sets/',
    [SetController::class, 'create']
);

Route::put(
    'v1/sets/{setId}',
    [SetController::class, 'put']
);

Route::patch(
    'v1/sets/{setId}',
    [SetController::class, 'patch']
);

Route::delete(
    'v1/sets/{setId}',
    [SetController::class, 'delete']
);

Route::get(
    'v1/workouts/{workoutId}',
    [WorkoutController::class, 'getById']
);

Route::get(
    'v1/workouts',
    [WorkoutController::class, 'getAll']
);

Route::post(
    'v1/workouts/',
    [WorkoutController::class, 'create']
);

Route::put(
    'v1/workouts/{workoutId}',
    [WorkoutController::class, 'put']
);

Route::patch(
    'v1/workouts/{workoutId}',
    [WorkoutController::class, 'patch']
);

Route::delete(
    'v1/workouts/{workoutId}',
    [WorkoutController::class, 'delete']
);
