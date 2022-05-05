<?php

namespace App\Domain\MuscleGroup\Actions;

use App\Models\MuscleGroup;

class UpdateMuscleGroupByIdAction
{
    public function execute(int $muscleGroupId, array $fields):MuscleGroup
    {
        $muscleGroup = MuscleGroup::findOrFail($muscleGroupId);
        $muscleGroup->update($fields);

        return $muscleGroup;
    }
}
