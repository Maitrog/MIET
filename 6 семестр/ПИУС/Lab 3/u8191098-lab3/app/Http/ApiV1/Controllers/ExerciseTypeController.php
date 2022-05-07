<?php

namespace App\Http\ApiV1\Controllers;

use App\Domain\ExerciseType\Actions\CreateExerciseTypeAction;
use App\Domain\ExerciseType\Actions\DeleteExerciseTypeByIdAction;
use App\Domain\ExerciseType\Actions\GetAllExerciseTypeAction;
use App\Domain\ExerciseType\Actions\GetExerciseTypeByIdAction;
use App\Domain\ExerciseType\Actions\UpdateExerciseTypeByIdAction;
use App\Http\ApiV1\Requests\ExerciseTypeRequests\CreateExerciseTypeRequest;
use App\Http\ApiV1\Requests\ExerciseTypeRequests\UpdateExerciseTypeRequest;
use App\Http\ApiV1\Resources\ExerciseTypeResource;

class ExerciseTypeController
{
    public function create(
        CreateExerciseTypeRequest $request,
        CreateExerciseTypeAction $action
    ) {
        return new ExerciseTypeResource($action->execute($request->validated()));
    }

    public function put(
        int $exerciseTypeId,
        UpdateExerciseTypeRequest $request,
        UpdateExerciseTypeByIdAction $action
    ) {
        return new ExerciseTypeResource(
            $action->execute(
                $exerciseTypeId,
                $request->validated()
            )
        );
    }

    public function delete(
        int $exerciseTypeId,
        DeleteExerciseTypeByIdAction $action
    ) {
        return new ExerciseTypeResource($action->execute($exerciseTypeId));
    }

    public function getById(
        int $exerciseTypeId,
        GetExerciseTypeByIdAction $action
    ) {
        return new ExerciseTypeResource(
            $action->execute($exerciseTypeId)
        );
    }

    public function getAll(
        GetAllExerciseTypeAction $action
    ) {
        $exerciseTypes = $action->execute();
        return response()->json($exerciseTypes);
    }
}
