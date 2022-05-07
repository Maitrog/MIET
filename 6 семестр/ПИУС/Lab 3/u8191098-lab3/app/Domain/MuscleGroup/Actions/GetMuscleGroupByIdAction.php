<?php

namespace App\Domain\MuscleGroup\Actions;

use App\Models\MuscleGroup;

class GetMuscleGroupByIdAction
{
    public function execute(int $muscleGroupId) :MuscleGroup
    {
        return MuscleGroup::findOrFail($muscleGroupId);
    }
}
