<?php

namespace App\Http\ApiV1\Controllers;

use App\Domain\MuscleGroup\Actions\CreateMuscleGroupAction;
use App\Domain\MuscleGroup\Actions\DeleteMuscleGroupByIdAction;
use App\Domain\MuscleGroup\Actions\GetAllMuscleGroupAction;
use App\Domain\MuscleGroup\Actions\GetMuscleGroupByIdAction;
use App\Domain\MuscleGroup\Actions\UpdateMuscleGroupByIdAction;
use App\Http\ApiV1\Requests\MuscleGroupRequests\CreateMuscleGroupRequest;
use App\Http\ApiV1\Requests\MuscleGroupRequests\UpdateMuscleGroupRequest;
use App\Http\ApiV1\Resources\MuscleGroupResource;

class MuscleGroupController
{
    public function create(
        CreateMuscleGroupRequest $request,
        CreateMuscleGroupAction $action
    ) {
        return new MuscleGroupResource($action->execute($request->validated()));
    }

    public function put(
        int $muscleGroupId,
        UpdateMuscleGroupRequest $request,
        UpdateMuscleGroupByIdAction $action
    ) {
        return new MuscleGroupResource(
            $action->execute(
                $muscleGroupId,
                $request->validated()
            )
        );
    }

    public function delete(
        int $muscleGroupId,
        DeleteMuscleGroupByIdAction $action
    ) {
        return new MuscleGroupResource($action->execute($muscleGroupId));
    }

    public function getById(
        int $muscleGroupId,
        GetMuscleGroupByIdAction $action
    ) {
        return new MuscleGroupResource(
            $action->execute($muscleGroupId)
        );
    }

    public function getAll(
        GetAllMuscleGroupAction $action
    ) {
        $muscleGroups = $action->execute();
        return response()->json($muscleGroups);
    }
}
