<?php

namespace App\Domain\MuscleGroup\Actions;

use App\Models\MuscleGroup;

class PatchMuscleGroupByIdAction
{
    public function execute(int $muscleGroupId, array $fields):MuscleGroup
    {
        return MuscleGroup::findOrFail($muscleGroupId)
        ->update($fields);
    }
}
