<?php

namespace App\Http\ApiV1\Controllers;

use App\Domain\Set\Actions\CreateSetAction;
use App\Domain\Set\Actions\DeleteSetByIdAction;
use App\Domain\Set\Actions\GetAllSetAction;
use App\Domain\Set\Actions\GetSetByIdAction;
use App\Domain\Set\Actions\PatchSetByIdAction;
use App\Domain\Set\Actions\UpdateSetByIdAction;
use App\Http\ApiV1\Requests\SetRequests\CreateSetRequest;
use App\Http\ApiV1\Requests\SetRequests\PatchSetRequest;
use App\Http\ApiV1\Requests\SetRequests\UpdateSetRequest;
use App\Http\ApiV1\Resources\SetResource;

class SetController
{
    public function create(
        CreateSetRequest $request,
        CreateSetAction $action
    ) {
        return new SetResource($action->execute($request->validated()));
    }

    public function put(
        int $setId,
        UpdateSetRequest $request,
        UpdateSetByIdAction $action
    ) {
        return new SetResource(
            $action->execute(
                $setId,
                $request->validated()
            )
        );
    }

    public function patch(
        int $setId,
        PatchSetRequest $request,
        PatchSetByIdAction $action
    ) {
        return new SetResource(
            $action->execute(
                $setId,
                $request->validated()
            )
        );
    }

    public function delete(
        int $setId,
        DeleteSetByIdAction $action
    ) {
        return new SetResource($action->execute($setId));
    }

    public function getById(
        int $setId,
        GetSetByIdAction $action
    ) {
        return new SetResource(
            $action->execute($setId)
        );
    }

    public function getAll(
        GetAllSetAction $action
    ) {
        $sets = $action->execute();
        return response()->json($sets);
    }
}
