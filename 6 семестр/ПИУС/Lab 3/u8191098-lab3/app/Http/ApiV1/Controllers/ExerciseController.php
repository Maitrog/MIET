<?php

namespace App\Http\ApiV1\Controllers;

use App\Domain\Exercise\Actions\CreateExerciseAction;
use App\Domain\Exercise\Actions\DeleteExerciseByIdAction;
use App\Domain\Exercise\Actions\GetAllExerciseAction;
use App\Domain\Exercise\Actions\GetExerciseByIdAction;
use App\Domain\Exercise\Actions\PatchExerciseByIdAction;
use App\Domain\Exercise\Actions\UpdateExerciseByIdAction;
use App\Http\ApiV1\Requests\ExerciseRequests\CreateExerciseRequest;
use App\Http\ApiV1\Requests\ExerciseRequests\PatchExerciseRequest;
use App\Http\ApiV1\Requests\ExerciseRequests\UpdateExerciseRequest;
use App\Http\ApiV1\Resources\ExerciseResource;

class ExerciseController
{
    public function create(
        CreateExerciseRequest $request,
        CreateExerciseAction $action
    ) {
        return new ExerciseResource($action->execute($request->validated()));
    }

    public function put(
        int $exerciseId,
        UpdateExerciseRequest $request,
        UpdateExerciseByIdAction $action
    ) {
        return new ExerciseResource(
            $action->execute(
                $exerciseId,
                $request->validated()
            )
        );
    }

    public function patch(
        int $exerciseId,
        PatchExerciseRequest $request,
        PatchExerciseByIdAction $action
    ) {
        return new ExerciseResource(
            $action->execute(
                $exerciseId,
                $request->validated()
            )
        );
    }

    public function delete(
        int $exerciseId,
        DeleteExerciseByIdAction $action
    ) {
        return new ExerciseResource($action->execute($exerciseId));
    }

    public function getById(
        int $exerciseId,
        GetExerciseByIdAction $action
    ) {
        return new ExerciseResource(
            $action->execute($exerciseId)
        );
    }

    public function getAll(
        GetAllExerciseAction $action
    ) {
        $exercises = $action->execute();
        return response()->json($exercises);
    }
}
