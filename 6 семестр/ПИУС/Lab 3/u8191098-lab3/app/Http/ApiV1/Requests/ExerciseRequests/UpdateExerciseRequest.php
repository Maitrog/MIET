<?php

namespace App\Http\ApiV1\Requests\ExerciseRequests;

use Illuminate\Foundation\Http\FormRequest;

class UpdateExerciseRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'name' => 'string|max:255|unique:exercises,name',
            'exercise_type_id' => 'exists:exercise_types,id',
            'muscle_group_id' => 'exists:muscle_groups,id',
        ];
    }
}
