<?php

namespace App\Domain\MuscleGroup\Actions;

use App\Models\MuscleGroup;

class DeleteMuscleGroupByIdAction
{
    public function execute(int $muscleGroupId)
    {
        $muscleGroup = MuscleGroup::findOrFail($muscleGroupId);
        $muscleGroup->delete();

        return $muscleGroup;
    }
}
