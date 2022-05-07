<?php

namespace App\Http\ApiV1\Controllers;

use App\Domain\Workout\Actions\CreateWorkoutAction;
use App\Domain\Workout\Actions\DeleteWorkoutByIdAction;
use App\Domain\Workout\Actions\GetAllWorkoutAction;
use App\Domain\Workout\Actions\GetWorkoutByIdAction;
use App\Domain\Workout\Actions\PatchWorkoutByIdAction;
use App\Domain\Workout\Actions\UpdateWorkoutByIdAction;
use App\Http\ApiV1\Requests\WorkoutRequests\CreateWorkoutRequest;
use App\Http\ApiV1\Requests\WorkoutRequests\PatchWorkoutRequest;
use App\Http\ApiV1\Requests\WorkoutRequests\UpdateWorkoutRequest;
use App\Http\ApiV1\Resources\WorkoutResource;

class WorkoutController
{
    public function create(
        CreateWorkoutRequest $request,
        CreateWorkoutAction $action
    ) {
        return new WorkoutResource($action->execute($request->validated()));
    }

    public function put(
        int $workoutId,
        UpdateWorkoutRequest $request,
        UpdateWorkoutByIdAction $action
    ) {
        return new WorkoutResource(
            $action->execute(
                $workoutId,
                $request->validated()
            )
        );
    }

    public function patch(
        int $workoutId,
        PatchWorkoutRequest $request,
        PatchWorkoutByIdAction $action
    ) {
        return new WorkoutResource(
            $action->execute(
                $workoutId,
                $request->validated()
            )
        );
    }

    public function delete(
        int $workoutId,
        DeleteWorkoutByIdAction $action
    ) {
        return new WorkoutResource($action->execute($workoutId));
    }

    public function getById(
        int $workoutId,
        GetWorkoutByIdAction $action
    ) {
        return new WorkoutResource(
            $action->execute($workoutId)
        );
    }

    public function getAll(
        GetAllWorkoutAction $action
    ) {
        $workouts = $action->execute();
        return response()->json($workouts);
    }
}
